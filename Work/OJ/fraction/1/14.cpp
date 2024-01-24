#include "utility.h"

template <void *_Ptr = nullptr>
struct tester : anti_hacker <_Ptr> {
    // Anti-hack!
    template <typename _Tp>
    using frac = typename anti_hacker <_Ptr>::template frac <_Tp>;

    using ll = long long;
    static_assert (sizeof (ll) == 8, "ll is not 64-bit integer.");

    static ll gen() { return my_rand() % 33; }

    // Real program here.
    void operator () () const {
        for (int i = 0 ; i < 114514 ; ++i) my_rand();
        for (int i = 0 ; i < 1000 ; ++i) {
            if (!frac <ll> { gen() - 15, gen() + 1 })
                std::cout << i << ' ';
        } std::cout << '\n';
    }
};

signed main() {
    anti_hack <tester <>> ();
    return 0;
}
