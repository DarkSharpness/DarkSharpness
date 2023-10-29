#include <bits/stdc++.h>
using namespace std;

int n;
int ans = 0;
int b[15];

void dfs(int x,int y) {
    if (x > n) { ++ans; return; }
    for(int i = 1; i < y - 1; ++i) {
        if (!b[i]) {
            b[i] = 1;
            dfs(x + 1,i);
            b[i] = 0;
        }
    }
    for(int i = y + 2; i <= n; ++i) {
        if (!b[i]) {
            b[i] = 1;
            dfs(x + 1,i);
            b[i] = 0;
        }
    }
}

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        n = i;
        freopen(in.c_str(),"w",stdout);
        cout << n << endl;
        freopen(out.c_str(),"w",stdout);
        ans = 0;
        dfs(1, -1);
        cout << ans << endl;
    }
    return 0;
}
