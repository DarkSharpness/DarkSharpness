#include "utility.h"

template <void *_Ptr = nullptr>
struct tester : anti_hacker <_Ptr> {
    // Anti-hack!
    template <typename _Tp>
    using frac = typename anti_hacker <_Ptr>::template frac <_Tp>;

    // Real program here.
    void operator () () const {
        frac <int> x;
        frac <int> y {-100};
        frac <long long> z {100,-1000};

        std::cout << x << ' ' << y << ' ' << z << '\n';

        (x = {1,-2}) = {-1919810};
        y = {114,514};
        z = {};

        std::cout << x << ' ' << y << ' ' << z << '\n';
    }
};

signed main() {
    anti_hack <tester <>> ();
    return 0;
}
