#include <bits/stdc++.h>
// #include <Dark/inout>


struct X {
    int value = 1;
    template<typename Self>
    void foo(this Self &&cur, int z) {
        cur.value += z;
    }

    void print() {
        std::cout << value << '\n';
    }
};
 
struct D : X {};
 
void ex(X& x, D& d) {
    x.foo(1);               // Self = X&
    std::move(x).foo(2);    // Self = X
    d.foo(3);               // Self = D&
    x.print();
    d.print();
}

signed main() {
    X a; D d;
    ex(a,d);
    return 0;
}