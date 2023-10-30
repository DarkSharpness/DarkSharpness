#include <bits/stdc++.h>


struct matrix {
    template <typename... Args>
    int operator[] (Args... args) { return (args + ...); }
};

signed main() {
    matrix a;
    std::cout << a[1,2,3,4,5,6,7] << '\n';
    return 0;
}