#include "utility.h"

template <void *_Ptr = nullptr>
struct tester : anti_hacker <_Ptr> {
    // Anti-hack!
    template <typename _Tp>
    using frac = typename anti_hacker <_Ptr>::template frac <_Tp>;

    using ll = long long;
    static_assert (sizeof (ll) == 8, "ll is not 64-bit integer.");

    static void exception_test() {
        try {
            ~frac <ll> { 0 , -1145141919810ll };
        } catch (std::exception &e) {
            std::cout << e.what() << '\n';
        }
        try {
            frac <ll> x { 0 , 1145141919810ll };
            x /= x;
        } catch (std::exception &e) {
            std::cout << e.what() << '\n';
        }
    }

    static void simplify_test() {
        frac <ll> sum;
        for (int i = 2 ; i <= 1000 ; ++i) sum += ~frac <ll> { i * i - 1 };
        std::cout << sum << '\n';    
        sum = {};
        for (int i = 1 ; i <= 30 ; ++i) sum -= ~-frac <ll> { 1 << i };
        std::cout << sum << '\n';
        sum -= (-frac <ll> { -1 , -(1 << 30) }) * (1ll);
        std::cout << - - - -(-sum + 1) << '\n';
    }

    // Real program here.
    void operator () () const {
        exception_test();
        simplify_test();
    }
};

signed main() {
    anti_hack <tester <>> ();
    return 0;
}
