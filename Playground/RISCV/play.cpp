#include "utility.h"
#include <iostream>
using namespace dark;

signed main() {
    std::cout << take <30,1> (-1) << '\n';
    switch (1) {
        default: throw;
        case 1: std::cout << "pass\n";
    }
    return 0;
}