#include "utility.h"

template <void *_Ptr = nullptr>
struct tester : anti_hacker <_Ptr> {
    // Anti-hack!
    template <typename _Tp>
    using frac = typename anti_hacker <_Ptr>::template frac <_Tp>;

    using ll = long long;
    static_assert (sizeof (ll) == 8, "ll is not 64-bit integer.");

    static void corner_test() {
        frac <ll> x {1 ,-114514ll };

        x /= x;
        std::cout << x << '\n';

        x = 1919ll;
        x *= x;
        std::cout << x << '\n';

        x /= 810ll;
        x += x;
        std::cout << x << '\n';

        x -= x;
        std::cout << x << '\n';

        x = {514ll,-1919ll};
        frac <ll> y = -~x;

        std::cout << x << ' ' << y << '\n';

        x -= y; 
        y += x;
        x = y - x;

        // swap (x, y);
        std::cout << x << ' ' << y << '\n';

        auto z = std::move (x);
        std::cout << z << '\n';
    }

    // Real program here.
    void operator () () const { corner_test(); }
};

signed main() {
    freopen("18.tmp", "w", stdout);
    anti_hack <tester <>> ();
    return 0;
}
