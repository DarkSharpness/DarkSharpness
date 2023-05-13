#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

const int N = 10;
const int M = 5;
int a[2][120][120];

signed main() {
    srand(time(NULL));
    for(int tt = 1 ; tt <= 10 ; ++tt) {
        string in  = to_string(tt) + ".in";
        string out = to_string(tt) + ".out";
        freopen(in.c_str(),"w",stdout);
        memset(a,0,sizeof(a));
        int n = rand() % N + 1;
        int m = rand() % N + 1;
        int k = rand() % M + 1;
        dark::writeline(n,m,k);
        for(int i = 1 ; i <= n ; ++i)
            for(int j = 1 ; j <= m ; ++j)
                a[0][i][j] = rand() % N;
        for(int i = 1 ; i <= n ; ++i) {
            for(int j = 1 ; j <= m ; ++j)
                dark::print(a[0][i][j],' ');
            dark::writeline();
        }
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
        freopen(out.c_str(),"w",stdout);
        for(int i = 1 ; i <= n ; ++i) {
            for(int j = 1 ; j <= m ; ++j)
                dark::print(a[t][i][j],' ');
            dark::writeline();
        }
    }
    return 0;
}