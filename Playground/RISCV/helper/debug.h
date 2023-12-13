#pragma once
#ifdef _DEBUG
#include <iostream>
#endif


namespace dark {

struct debug {
    template <typename T, typename ...Args>
    debug(T &&v, Args &&...args) {
#ifdef _DEBUG
        std::cout << "\033[31m";
        std::cout << v;
        ((std::cout << ' ' << args),...);
        std::cout << "\033[0m\n";
#endif
    }
};


} // namespace dark