#pragma once
#include "utility.h"

namespace dark {

/**
 * @brief Register file for scalar registers.
 */
struct register_file {
    std::array <reg, 32> regs;  // Register file core data.
    std::array <reg, 32> dirty; // Whether result is on work.
};

} // namespace dark


namespace dark {

/**
 * @brief Register file for vector registers.
 */
struct vector_file {
    std::array <reg, VIDX * 32> regs;
};


} // namespace dark