// #include <bits/stdc++.h>
#include <Dark/Container/allocator.h>
#include <Dark/inout>
// #define int long long
// using ll = long long;
// using ull = unsigned long long;

dark::allocator <int> a;

signed main() {
    auto p = a.alloc();
    dark::writeline(*p);
    a.construct(p,2);
    dark::writeline(*p);
    return 0;
}