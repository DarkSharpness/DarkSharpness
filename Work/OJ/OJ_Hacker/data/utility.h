#pragma once
#include <cstdint>
#include <iostream>

namespace dark {

std::size_t rand() {
    static std::size_t seed = 0x1145141919810;
    seed ^= seed << 5;
    seed ^= seed >> 17;
    seed ^= seed << 13;
    return seed;
}

void check_print(std::size_t cnt) {
    while(cnt--) rand();
    std::cout << "Checksum: " <<  rand() << '\n';
}

} // namespace dark
