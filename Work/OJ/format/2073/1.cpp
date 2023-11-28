#include "src.hpp"
#include "utility.h"

#include <iostream>

signed main() {
    std::cout << sjtu::format("{0}{1}, {2}{2}{3}!\n", 114ll ,std::string("514") , 19, "810");
    return 0;
}
