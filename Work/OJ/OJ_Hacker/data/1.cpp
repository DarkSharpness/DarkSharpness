#include "src.hpp"
#include "utility.h"
#include <iostream>

signed main() {
    tester <int> x = 1;

    if (x == 1) std::cout << "Accepted!\n";
    else        std::cout << "Wrong answer!\n";

    return 0;
}
