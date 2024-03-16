#include <iostream>

constexpr char table[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

signed main() {
    int n,m;
    std::cin >> n >> m;
    int t = 0;
    char ans[64];
    for(; n != 0 ; ++t) {
        int x = n % m;
        if (x < 0) x -= m;
        ans[t] = table[x];
        n = (n - x) / m;
    }
    while(t --> 0) std::cout << ans[t];
    return 0;
}
