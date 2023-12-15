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
        std::cerr << "\033[31m";
        std::cerr << v;
        ((std::cerr << ' ' << args),...);
        std::cerr << "\033[0m\n";
#endif
    }
};

struct details {
    template <typename T, typename ...Args>
    details([[maybe_unused]]T &&v,[[maybe_unused]] Args &&...args) {
#ifdef _DETAIL
        std::cerr << "\033[32m";
        std::cerr << v;
        ((std::cerr << ' ' << args),...);
        std::cerr << "\033[0m\n";
#endif
    }
};



} // namespace dark