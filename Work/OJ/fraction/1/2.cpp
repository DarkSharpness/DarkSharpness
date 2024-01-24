#include "utility.h"

template <void *_Ptr = nullptr>
struct tester : anti_hacker <_Ptr> {
    // Anti-hack!
    template <typename _Tp>
    using frac = typename anti_hacker <_Ptr>::template frac <_Tp>;

    using ll = long long;
    static_assert (sizeof (ll) == 8, "ll is not 64-bit integer.");

    static ll gen() { return (int(my_rand()) >> 1); }

    // Real program here.
    void operator () () const {
        for (int i = 0 ; i < 514 ; ++i) my_rand();

        for (int j = 0 ; j < 20 ; ++j) {
            for (int i = 0 ; i < 20 ; ++i) {
                ll x = gen() % 9;
                ll y = gen() % 9;
                if (y == 0) y = -1 - (my_rand() & 7);
                std::cout << frac <ll> {x, y} << ' ';
            } std::cout << '\n';
        }
    }
};

signed main() {
    anti_hack <tester <>> ();
    return 0;
}
