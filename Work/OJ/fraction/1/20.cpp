#include "utility.h"

template <void *_Ptr = nullptr>
struct tester : anti_hacker <_Ptr> {
    // Anti-hack!
    template <typename _Tp>
    using frac = typename anti_hacker <_Ptr>::template frac <_Tp>;

    using ll = long long;
    static_assert (sizeof (ll) == 8, "ll is not 64-bit integer.");

    using _F128 = frac <__int128_t>;

    template <typename _Tp, typename _Up = int>
    static frac <_Tp> random_frac() {
        my_rand(), my_rand();
        return { _Up(my_rand()) , _Up(my_rand()) };
    }

    static _F128 rand_128() {
        int tmp = int(my_rand()) % 9;
        if (tmp == 0) tmp = 1;
        return { int(my_rand()) % 9 , tmp };
    }

    static void random_test() {
        std::cout << std::boolalpha;
        for (int i = 0 ; i < 100 ; ++i) {
            auto x = random_frac <__int128_t> ();
            std::cout
                << x + random_frac <__int128_t> () << ' '
                << x - random_frac <__int128_t> () << ' '
                << x * random_frac <__int128_t> () << ' '
                << x / random_frac <__int128_t> () << ' '
                << ~x << ' ' << -x << '\n';
        }

        for (int i = 0 ; i < 100 ; ++i) {
            auto x = random_frac <ll> ();
            std::cout
                << x + random_frac <ll, short> () << ' '
                << x - random_frac <ll, short> () << ' '
                << x * random_frac <ll, short> () << ' '
                << x / random_frac <ll, short> () << ' '
                << ~x << ' ' << -x << '\n';
        }

        for (int i = 0 ; i < 233 ; ++i) {
            std::cout
                << (rand_128() <   rand_128()) << ' '
                << (rand_128() ==  rand_128()) << '\n';
        }
    }

    // Real program here.
    void operator () () const { random_test(); }
};

signed main() {
    freopen("20.tmp", "w", stdout);
    anti_hack <tester <>> ();
    return 0;
}
