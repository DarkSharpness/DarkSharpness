#include "src.hpp"
#include "utility.h"

#include <iostream>

signed main() {
    std::string_view s  = "You may wonder why I use std::string_view here.\n{}";
    std::string message =
        "The reason is rather simple.\n"
        "When you just want to hold a reference to a string,\n"
        "but you don't want to modify it or copy it,\n"
        "you can use std::string_view as const reference.\n"
        "Why not const std::string &?\n"
        "If you initialize from a const char *,\n"
        "std::string_view will not allocate memory!\n"
        "It is a light-weight reference to a string.\n"
        "It provides a lot of useful functions, such as O(1) substr.\n";
    std::cout << sjtu::format(s, message);
    std::cout << sjtu::format("End! Hope to be useful for you!\n");
    return 0;
}
