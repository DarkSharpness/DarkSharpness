#ifndef TEST2
#define TEST2
#include <iostream>

#ifdef TEST1
    void print2() {
        std::cout << '1';
    }
#endif

#endif