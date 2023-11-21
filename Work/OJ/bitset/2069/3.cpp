#include "src.hpp"
#include "local.h"


template <class T = dynamic_bitset>
void test_func() {
    std::string a(64 * 114514 + 1,'1');
    std::string b(64 * 114514 + 1,'0');
    auto __print = [&]() -> void {
        std::cout
            << T {a}.none() << ' ' << T {a}.all() << '\n'
            << T {b}.none() << ' ' << T {b}.all() << '\n';
        std::cout << "--------------------------------\n";
    };

    __print();

    a.back() = '0';
    b.back() = '1';

    __print();

    a.pop_back();
    a.pop_back();

    a.back() = '0';
    a.back() = '1';

    b.pop_back();
    b.pop_back();

    __print();

    a[rand() % a.size()] = '0';
    b[rand() % b.size()] = '1';

    __print();
}


signed main() {
    test_func();
    return 0;
}
