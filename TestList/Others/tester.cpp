#include <bits/stdc++.h>
// #include <Dark/inout>

struct tester {
    int val = 2;
    tester *operator &  (void) noexcept {
        return this + 1;
    }
    tester *operator ->*(int x) noexcept {
        return this + 1;
    }
    
};

signed main() {
    tester x[2] = {{1},{3}};
    std::cout << x->val << ' ' << (&x[0])->val;
    return 0;
}