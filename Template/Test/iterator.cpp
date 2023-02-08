#include <iostream>
#include <Dark/memleak>
#include <Dark/iterator>

using dark::RandomAccess::iterator;
using dark::RandomAccess::const_iterator;
using dark::RandomAccess::reverse_iterator;
using dark::RandomAccess::const_reverse_iterator;

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
    std::cout << y->name << '\n';
    delete y.base();
    if(x == y) std::cout << "true\n";
    if(x != y) std::cout << "false\n";

    reverse_iterator <foo> tmp((new foo[2] {1,"AC",1.3}) + 1);
    const_reverse_iterator <foo> ttt = tmp + 1;

    std::cout << ttt->name << '\n';

    ++tmp;

    delete[] tmp.base();
    return 0;
}