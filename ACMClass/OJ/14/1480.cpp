#include <Dark/inout>

const int N = 1e6 + 3;
int mid[21][N]; // mid for [l,r]
int s[N];       // prefix sum of 0.
int LOG[N];

inline int max(int a,int b) { return a > b ? a : b; }

signed main() {
    int n,m;
    dark::read_u(n,m);
    for(int i = 1 ; i <= n ; ++i) s[i] = s[i - 1] + (dark::read_char() == '0');
    for(int l = 0 ; l <= n ; ++l) mid[0][l] = (s[l] << 1) - l;
    for(int i = 1,x ; (x = 1 << i) <= n ; ++i)
        for(int l = 0 ; l + x - 1 <= n ; ++l)
            mid[i][l] = max(mid[i - 1][l],mid[i - 1][l + (x >> 1)]);
    for(int i = 2 ; i <= n + 1 ; ++i) LOG[i] = LOG[i - 1] + !(i & (i - 1));
    while(m--) {
        char opt;
        int x,y;
        dark::read_char(opt);
        dark::read_u(x,y);
        if(opt == '1') {
            int t = LOG[y - x + 2];
            dark::writeline(
                max(mid[t][x - 1],mid[t][y - (1 << t) + 1]) - s[y] - s[x - 1] + y
            );
        } else {
            int t = s[y] - s[x - 1];
            dark::writeline(t == s[y] - s[y - t]  ? '1' : '2');
        }
    }
    return 0;
}
