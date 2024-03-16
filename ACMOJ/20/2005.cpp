#include <bits/stdc++.h>


signed main() {
    int a,b,c,d;
    std::cin >> a >> b >> c >> d;
    if (a == 0 && b == 0 && c == 0 && d == 0) {
        std::cout << 2000LL * 2000 * 2000 * 2000;
        return 0;
    }
    int cnt = (a > 0) + (b > 0) + (c > 0) + (d > 0);
    if (cnt == 0 || cnt == 4) {
        std::cout << 0;
        return 0;
    }
    std::unordered_map <int, int> mp;
    mp.reserve(1000 * 1000 + 2);
    for(int i = 1 ; i <= 1000 ; ++i) {
        const int x = a * i * i;
        for(int j = 1 ; j <= 1000 ; ++j)
            ++mp[x + b * j * j];
    }
    long long ans = 0;
    for(int i = 1 ; i <= 1000 ; ++i){
        const int y = c * i * i;
        for(int j = 1 ; j <= 1000 ; ++j) {
            auto it = mp.find(-(y + d * j * j));
            if (it != mp.end()) ans += it->second;
        }
    }
    std::cout << ans * 16;
    return 0;
}