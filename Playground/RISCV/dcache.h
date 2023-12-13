#pragma once
#include "utility.h"

namespace dark {

struct dcache {
    static constexpr int bias  = 6;
    static constexpr int size  = 1 << bias;
    static constexpr int width = 4;
    static constexpr int lines = 1 << width;

    std::array <reg, size * lines> dat;
    std::array <reg,        lines> tag;


};


} // namespace dark
