#include <bits/stdc++.h>

/* This already exists in C++17,but not 14...... */
template <class T>
constexpr int is_signed_v = std::is_signed <T>::value;

/* 可以特化 qwq */
template <>
constexpr int is_signed_v <int> = 114514;

signed main() {
    std::cout << is_signed_v <int> << '\n';
    return 0;
}