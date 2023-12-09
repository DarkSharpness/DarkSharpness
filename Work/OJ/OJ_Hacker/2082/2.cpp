#include "src.hpp"
#include "utility.h"

long long rand_in(long long x) { return dark::rand() % x; }

template <typename _Tp>
void test() {
    _Tp x = {2 , 4};        // behave like a fraction
    std::cout << x << '\n'; // print out 1/2 
    for (int i = 0 ; i < 20 ; ++i)
        x += _Tp { 1 , rand_in(30) };
    std::cout << x << '\n'; // print out the result
}

signed main() {
    test <fraction <long long>> ();
    for (int i = 0 ; i < 100 ; ++i) dark::rand();
    dark::check_print(1000);
    return 0;
}
