#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

const int N = 100;
int s[N + 1][N + 1];


signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        freopen(in.c_str(),"w",stdout);
        int n = rand() % N + 1;
        int m = rand() % N + 1;
        dark::writeline(n,m);
        for(int i = 1 ; i <= n ; ++i) {
            for(int j = 1 ; j <= m ; ++j) {
                s[i][j] = rand() % N + 1;
                dark::print(s[i][j],' ');
                s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
            }
            dark::writeline();
        }
        int a = rand() % n + 1;
        int b = rand() % m + 1;
        int c = rand() % (n - a + 1) + a;
        int d = rand() % (m - b + 1) + b;
        dark::writeline(a,b,c,d);
        freopen(out.c_str(),"w",stdout);
        dark::writeline(s[c][d] - s[c][b - 1] - s[a - 1][d] + s[a - 1][b - 1]);
    }
    return 0;
}