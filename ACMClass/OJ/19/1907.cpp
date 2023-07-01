#include <cmath>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include "src.h"

// Note: the NOLINT below is used to make clang-tidy ignore the warning.
// You are free to ignore it.

constexpr int kDataSize = M;
constexpr int kMaxPacketSize = N;
constexpr double kP1 = 0.4;
constexpr double kP2 = 0.0 / 1280.0;
constexpr double kA = 3;

uint8_t source[kDataSize];
uint8_t answer[kDataSize];
uint8_t buffer[kMaxPacketSize];

bool Choose(double p) {
    return rand() % 1000 < p * 1000; // NOLINT
}

void GenerateData(uint8_t* data, int dataSize) {
    srand(time(NULL)); // NOLINT
    for (int i = 0; i < dataSize; ++i) {
        data[i] = rand() % 256; // NOLINT
    }
}

int amount = 0;
void SendPacket(const uint8_t* data, int dataSize) {
    dataSize = std::min(dataSize, kMaxPacketSize);
    int size = std::min(dataSize, 10 * kDataSize - amount);
    if (amount >= 10 * kDataSize) return;
    amount += size;
    if (Choose(kP1)) return;
    for (int i = 0; i < size; ++i) {
        // Copy the data
        buffer[i] = data[i];
        // Corrupt the data
        for (int j = 0; j < 8; ++j) {
            if (Choose(kP2)) buffer[i] ^= (uint8_t(1) << j);
        }
    }
    for (int i = size; i < kMaxPacketSize; ++i) {
        buffer[i] = 0;
    }
    ReceivePacket(buffer, size, answer);
    for (unsigned char& i : buffer) { i = 0; }
}

double Evaluate(const uint8_t* answerArray, int dataSize) {
    unsigned long long sourceSum = 0;
    for (int i = 0; i < dataSize; ++i) {
        sourceSum += source[i];
    }
    uint8_t average = sourceSum / dataSize;
    unsigned long long tmp1 = 0;
    unsigned long long tmp2 = 0;
    for (int i = 0; i < dataSize; ++i) {
        tmp1 += (int(answerArray[i]) - int(source[i])) * (int(answerArray[i]) - int(source[i]));
        tmp2 += (int(source[i]) - int(average)) * (int(source[i]) - int(average));
    }
    double m1 = std::max(0.0, 1.0 - static_cast<double>(tmp1) / static_cast<double>(tmp2));
    double m2 = 1.0 - static_cast<double>(amount) / static_cast<double>(dataSize * 10);
    double score = m1 * pow(m2, kA) * 10000;
    std::cout << "M1: " << m1 << std::endl;
    std::cout << "M2: " << m2 << std::endl;
    std::cout << "Score: " << score << std::endl;
    return score;
}

int main() {
    GenerateData(source, kDataSize);
    for (unsigned char& i : answer) i = 0;
    Send(kMaxPacketSize, kP1, kP2, source, kDataSize, kA);
    Evaluate(answer, kDataSize);
}