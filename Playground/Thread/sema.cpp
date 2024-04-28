#include <iostream>
#include <format>
#include <semaphore>
#include <atomic>
#include <thread>
#include <cmath>
#include <random>

constexpr size_t kSIZE = 128;

char buffer[kSIZE + 1];
constexpr char *buffer_end = buffer + kSIZE;
std::atomic <char *> head = buffer;
std::atomic <char *> tail = buffer;
std::atomic <size_t> release_times = 0;
std::atomic <size_t> acquire_times = 0;

std::counting_semaphore sem(0);

void producer(char c) {
    std::mt19937 gen(std::random_device{}());
    using namespace std::chrono_literals;
    for (char *pos; (pos = tail.fetch_add(1)) < buffer_end ;) {
        *pos = c;
        sem.release();
        release_times.fetch_add(1);

        double ratio  = (gen() - gen.min()) / double(gen.max() - gen.min());
        double factor = std::lerp(0.1, 0.5, ratio);
        std::this_thread::sleep_for(1s * factor);
    }
    std::cout << std::format("Producer \"{}\" is over\n", c);
    sem.release();
}

void consumer(char c) {
    std::mt19937 gen(std::random_device{}());
    using namespace std::chrono_literals;
    while (true) {
        sem.acquire();
        char *pos = head.fetch_add(1);
        if (pos >= buffer_end) break;

        acquire_times.fetch_add(1);
        std::cout << std::format("[{:2} -> {}]\n", pos - buffer, *pos);

        double ratio  = (gen() - gen.min()) / double(gen.max() - gen.min());
        double factor = std::lerp(0.1, 0.5, ratio);
        std::this_thread::sleep_for(1s * factor);
    }
    std::cout << std::format("Consumer \"{}\" is over\n", c);
}

signed main() {
    constexpr size_t kSIZE = 26;
    std::thread consumer[kSIZE];
    std::thread producer[kSIZE];

    for (auto &c : consumer) c = std::thread(::consumer, char('a' + (&c - consumer)));
    for (auto &p : producer) p = std::thread(::producer, char('a' + (&p - producer)));

    for (auto &c : consumer) c.join();
    for (auto &p : producer) p.join();

    std::cout << std::format("{:-<30}\n", "");
    std::cout << std::format(
        "Release times: {}\n"
        "Acquire times: {}\n",
        release_times.load(), acquire_times.load());

    return 0;
}
