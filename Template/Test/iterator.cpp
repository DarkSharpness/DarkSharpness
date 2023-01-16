#include <iostream>
#include <Dark/memleak>
#include <Dark/iterator>

using dark::RandomAccess::iterator;
using dark::RandomAccess::const_iterator;


struct foo {
    int x;
    char name[4];
    double y;
};

signed main() {
    iterator <foo> x(new foo {1,"ab",1.3});
    const_iterator <foo> y = x;
    --x;
    --x;
    std::cout << y - x << '\n';
    x = x + -2;
    x += 4;
    y = x;
    x->name[0] = 'c';
    std::cout << y->name;
    delete y.base();
    return 0;
}