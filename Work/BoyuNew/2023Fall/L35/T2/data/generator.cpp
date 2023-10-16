#include <bits/stdc++.h>
using namespace std;

template <size_t __N,size_t __M>
size_t better_rand() {
    if constexpr (__N == 0) return rand();
    else return rand() ^ (better_rand<__N - 1,__M>() << __M);
}

const unsigned long long N = 5e3;


signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        const int M = i * i * 50;

        int n = better_rand <10,10> () % M + 1;
        int m = better_rand <10,10> () % M + 1;
        int c = better_rand <10,10> () % M + 1;

        // Re-decide!
        if (c > n + 2 * m) c = better_rand <10,10> () % M + 1;

        freopen(in.c_str(),"w",stdout);
        std::cout << n << ' ' << m << ' ' << c << '\n';

        while (n--)
            std::cout << better_rand <10,10> () % N + 1 << ' ';
        std::cout << '\n';

        while (m--)
            std::cout << better_rand <10,10> () % N + 1 << ' ' << '\n';
    }
    return 0;
}