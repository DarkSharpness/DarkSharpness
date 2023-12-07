#pragma once
#include <cstdint>

namespace dark {

std::size_t rand() {
    static std::size_t seed = 0x2023;
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}

} // namespace dark

