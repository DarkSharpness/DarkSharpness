#include <iostream>

const int N = 1e5 + 3;
int f[N];

/* 请不要抄袭! */
signed main() {
    int n,x,c;
    std::cin >> n >> x >> c;
    f[2] = -x;
    for(int i = 4 ; i <= n + 1 ; i += 2) {
        f[i] = f[i >> 1] + c;
        f[i - 1] = f[i] + x; 
    }
    int ans = 0;
    for(int i = 2 ; i <= n ; ++i)
        ans = std::max(ans,f[i]);
    std::cout << ans << '\n';
    return 0;
}
