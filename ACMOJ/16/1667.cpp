#include <iostream>
#include <bitset>

const int M = 8;    /* 8-bits */
std::bitset <1 << M> bits;

char read_char() {
    char c;
    while((c = getchar()) != '0' && c != '1');
    return c;
}

signed main() {
    for(int i = 0 ; i < (1 << M) ; ++i)
        if (read_char() == '1') bits.set(i);

    std::bitset <M> ans = {};
    for(int i = 0 ; i < (1 << M) ; ++i) {
        bool current = bits[i];
        if (!current) continue;
        for(int j = 0 ; j < M ; ++j)
            if ((i >> j) & 1) ans.flip(j);
    }

    std::cout << ans.to_ulong() << std::endl;
    return 0;
}
