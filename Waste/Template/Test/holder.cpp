#include <bits/stdc++.h>



template <class T,class ...V>
struct holder : holder <V...> {
    T data;
    template <size_t __n>
    auto &arg() noexcept {
        if constexpr(__n) return holder <V...> ::arg <__n - 1>();
        else              return data;
    }
};

template <class T>
struct holder <T> {
    T data;
    template <size_t __n>
    T &arg() noexcept {
        static_assert(!__n);
        return data;
    }
};

signed main() {
    holder <int,long long> h {2,3}; 
    auto x = h.arg <0> (); 
    return 0;
}