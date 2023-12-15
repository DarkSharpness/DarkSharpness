#pragma once
#ifdef _DEBUG
#include <iostream>
#endif
#ifdef _DETAIL
#include <iostream>
#endif


namespace dark {

struct debug {
    template <typename T, typename ...Args>
    debug([[maybe_unused]]T &&v,[[maybe_unused]] Args &&...args) {
#ifdef _DEBUG
        std::cout << "\033[31m";
        std::cout << v;
        ((std::cout << ' ' << args),...);
        std::cout << "\033[0m\n";
#endif
    }
};

struct details {
    template <typename T, typename ...Args>
    details([[maybe_unused]]T &&v,[[maybe_unused]] Args &&...args) {
#ifdef _DETAIL
        std::cout << "\033[32m";
        std::cout << v;
        ((std::cout << ' ' << args),...);
        std::cout << "\033[0m\n";
#endif
    }
};



} // namespace dark