#pragma once

#include "helper/hardware.h"
#include "helper/reflect.h"
#include "helper/bits.h"


namespace dark {

inline void assert(bool cond, std::string_view msg = "") {
    if (!cond) throw std::runtime_error(std::string(msg));
}

// Vector extension part.

inline constexpr int VLEN {64}; // 64bits
inline constexpr int VIDX {2} ; // 2 registers per unit.


} // namespace dark