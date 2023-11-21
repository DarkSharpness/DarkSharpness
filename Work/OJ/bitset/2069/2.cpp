#include "src.hpp"
#include "local.h"


template <class T = dynamic_bitset>
std::size_t push_backer() {
    T x;
    for (int i = 0 ; i < 1919810 ; ++i) x.push_back(i & 1);
    for (int i = 0 ; i < 114514 ; ++i)
        x.set(my_rand() % x.size(), my_rand() & 1);
    std::size_t sum = 0;
    for (std::size_t i = 0 ; i != x.size() ; ++i) sum += x[i];
    return sum;
}


signed main() {
    std::cout << push_backer() << '\n';
    return 0;
}
