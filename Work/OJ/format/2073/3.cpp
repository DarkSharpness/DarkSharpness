#include "src.hpp"
#include "utility.h"

#include <iostream>

signed main() {
    std::string x   = "Dark";
    const char y[]  = "Hastin";
    long long test  = -1;
    std::cout << sjtu::format("{2} {0}! test: {1}!\n" , x, y, test);
    return 0;
}
