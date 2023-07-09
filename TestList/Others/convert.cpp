#include <bits/stdc++.h>

struct B;

struct A {
    // bool operator == (const B &) const {
    //     std::cout << "A == B\n";
    //     return false;
    // }
};

struct B {
    B() = default;
    B(const A &) {}
    // bool operator == (const B &) const {
    //     std::cout << "class B == B\n";
    //     return false;
    // }
};

bool operator == (const A &,const A &) {
    std::cout << "A == A\n";
    return true;
}

bool operator == (const B &,const B &) {
    std::cout << "B == B\n";
    return true;
}

bool operator == (const B &,const A &) {
    std::cout << "B == A\n";
    return true;
}

// bool operator == (const A &,const B &) {
//     std::cout << "A == B\n";
//     return true;
// }


signed main() {
    A x,y;
    B c,d;
    x == y;
    x == c;
    c == x;
    c == d;
    // std::cout << (x == y) << '\n';
    return 0;
}
