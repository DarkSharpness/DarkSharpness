#include <bits/stdc++.h>
#include <Dark/inout>

template <size_t __n>
struct number_test {
    constexpr static size_t data = __n;
};

template <>
struct number_test <0> {
    constexpr static size_t data = 1;
};


signed main() {
    dark::writeline(number_test <1>::data,number_test <0>::data);
    std::numeric_limits <void>;

    return 0;
}