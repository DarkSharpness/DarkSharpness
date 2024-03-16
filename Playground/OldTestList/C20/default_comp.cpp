#include <bits/stdc++.h>
// #include <Dark/inout>

struct test {
    int val;

    // bool operator == (const test &rhs) const = default;

    // friend bool operator <= (const test &,const test &) = default;
    friend bool operator == (const test &,const test &) = default;

    friend auto operator <=> (const test &,const test &) = default;

};

struct custom {
    double val;

    // bool operator == (const test &rhs) const = default;

    // friend bool operator <= (const test &,const test &) = default;
    friend bool operator ==  (const custom &,const custom &) = default;

    friend auto operator <=> (const custom &,const custom &) = default;

};

signed main() {
    test x{.val = 1};
    test y{.val = 2};
    std::cout << std::boolalpha;
    std::cout << (x == y) << ' ' << (x != y) << '\n';
    std::cout << (test{1} <= test{2}) << '\n';

    auto r = custom {NAN} == custom{NAN};
    std::cout << r << '\n';
    auto rr = custom {1} <=> custom{NAN};
    std::cout << (rr == std::partial_ordering::unordered) << '\n';

    return 0;
}