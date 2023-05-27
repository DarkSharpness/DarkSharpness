#include <bits/stdc++.h>
using namespace std;

const int N = 102;

int a[2][N][N]; // 不滚动数组也能做哦

signed main() {
    int n,m,k;
    cin >> n >> m >> k;
    for(int i = 1 ; i <= n ; ++i)
        for(int j = 1 ; j <= m ; ++j)
            cin >> a[0][i][j];
    bool t = false;
    while(k--) {
        for(int i = 1 ; i <= n ; ++i)
            for(int j = 1 ; j <= m ; ++j) {
                a[!t][i][j] = 0;
                for(int x = -1 ; x <= 1 ; ++x)
                    for(int y = -1; y <= 1 ; ++y)
                        a[!t][i][j] += a[t][i + x][j + y];
                int x = 3,y = 3;
                if(i == 1) --x;
                if(i == n) --x;
                if(j == 1) --y;
                if(j == m) --y;
                a[!t][i][j] /= x * y;
            }
        t = !t;
    }
    for(int i = 1 ; i <= n ; ++i) {
        for(int j = 1 ; j <= m ; ++j)
            cout << a[t][i][j] << ' ';
        cout << '\n';
    }
    return 0;
}