#include "src.hpp"
#include "utility.h"

#include <iostream>

signed main() {
    std::string str[2];
    str[0] = "Genshin";
    str[1] = "Impact";
    unsigned long long test = -1;
    std::cout << sjtu::format("{} {}!\n" , str[0], str[1], test);
    std::cout << sjtu::format("{} {}! test : {}!\n" , str[0], str[1], test);
    return 0;
}
