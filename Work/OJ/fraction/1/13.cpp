#include "utility.h"

template <void *_Ptr = nullptr>
struct tester : anti_hacker <_Ptr> {
    // Anti-hack!
    template <typename _Tp>
    using frac = typename anti_hacker <_Ptr>::template frac <_Tp>;

    using ll = long long;
    static_assert (sizeof (ll) == 8, "ll is not 64-bit integer.");

    static ll gen() { return (int(my_rand()) >> 1); }

    static bool equal(double x, double y) {
        const double sub    = std::abs(x - y);
        const double eps    = 1e-6;
        return (sub < eps) || (sub / x < eps); 
    }

    // Real program here.
    void operator () () const {
        for (int i = 0 ; i < 114514 ; ++i) my_rand();
        for (int i = 0 ; i < 100 ; ++i) {
            long long x = gen();
            if (x == 0) x = 1;
            long long y = gen();
            if (y == 0) y = 1;
            std::cout << equal(double(x) / y, double(frac <ll> {x, y}));
        } std::cout << '\n';
    }
};

signed main() {
    anti_hack <tester <>> ();
    return 0;
}
