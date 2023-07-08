#include <iostream>
#include <cstring>

int x[20],y[20],z[20];
int n,m,ans;

/* 请不要抄袭! */
signed main() {
    std::cin >> n >> m;
    for(int i = 0 ; i < m ; ++i)
        std::cin >> x[i] >> y[i] >> z[i];

    int ans = 0;
    for(int i = 0 ; i < (1 << n) ; ++i) {
        bool flag = false;
        for(int j = 0 ; j < m ; ++j) {
            bool __x = (i >> x[j]) & 1;
            bool __y = (i >> y[j]) & 1;
            if((__x ^ __y) != z[j]) {
                flag = true;
                break;
            }
        } if(flag) continue;
        ++ans;
    }
    std::cout << ans << '\n';
    return 0;
}
