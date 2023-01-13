// #pragma GCC optimize(3)
#include <Dark/memleak>
#include <Dark/dynamic_array>
#include <bits/stdc++.h>
#include <conio.h>
using dark::dynamic_array;
using std::vector;

template <class T>
void print(const T &A) {
    for(auto &it : A) std::cout << it << ' ';
    std::cout << '\n' << A.size() << ' ' << A.capacity() << '\n';
}

struct foo {
    int x;
    foo(const char *) {std::cout << "Construction\n";}
    foo(foo &&) {std::cout << "Move Construction\n";}
    foo(const foo &) {std::cout << "Copy Construction\n";}

    foo &operator =(foo &&) {
        std::cout << "Move Assign\n";
        return *this;
    }
    foo &operator =(const foo &) {
        std::cout << "Copy Assign\n";
        return *this;
    }

};


signed main() {
    using Container = dynamic_array <std::string>;
    Container A = Container {"abcd","123","777"};
    std::cout << "------------------------------\n";
    A.push_back("_123");
    std::cout << "------------------------------\n";
    A.push_back("CON","HST","DARK");
    std::cout << "------------------------------\n";
    A.emplace_back("123123");
    
    Container B = {"abc","def"};
    A = B;
    print(A);
    print(B);
    dark::LOG2(2);
    return 0;
}