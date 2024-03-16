#include <bits/stdc++.h>
// #include <Dark/inout>


signed main() {
    std::unordered_set <int> m;
    m.reserve(1000);
    static_assert(sizeof(m.begin()) == 8);
    m.insert(6);
    m.insert(3);
    m.insert(5);
    m.insert(4);
    for(auto iter : m)
        std::cout << iter << '\n';
    return 0;
}