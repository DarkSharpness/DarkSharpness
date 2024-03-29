#include "utility.h"

template <void *_Ptr = nullptr>
struct tester : anti_hacker <_Ptr> {
    // Anti-hack!
    template <typename _Tp>
    using frac = typename anti_hacker <_Ptr>::template frac <_Tp>;

    using ll = long long;
    static_assert (sizeof (ll) == 8, "ll is not 64-bit integer.");

    static ll gen() { return (int(my_rand()) >> 1); }

    static frac <ll> rand_frac() {
        ll x = gen() % 1000;
        ll y = gen() % 1000;
        if (!y) y = 1 + (my_rand() % 1023);
        return frac <ll> {x, y};
    }

    // Real program here.
    void operator () () const {
        for (int i = 0 ; i < 1919 ; ++i) my_rand();

        for (int j = 0 ; j < 10 ; ++j) {
            for (int i = 0 ; i < 10 ; ++i) {
                auto ttmp = rand_frac();
                ttmp -= rand_frac();
                std::cout << ttmp << ' ';
            } std::cout << '\n';
        }

        for (int i = 0 ; i < 810 ; ++i) my_rand();

        for (int j = 0 ; j < 5 ; ++j) {
            for (int i = 0 ; i < 5 ; ++i) {
                auto ttmp = rand_frac();
                ttmp -= gen() % 114;
                std::cout << ttmp << ' ';
            } std::cout << '\n';
        }
    }
};

signed main() {
    anti_hack <tester <>> ();
    return 0;
}
