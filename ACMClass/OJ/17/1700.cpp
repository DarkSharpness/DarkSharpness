#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 2008;
ll c[N][N];
ll f[N][N];
/// @brief Fast read-in.
inline void read(ll &tmp) {
    static char ch;
    tmp = 0;
    while(!isdigit(ch = getchar()));
    while(isdigit(ch)) {
        tmp = (tmp<<1) + (tmp<<3) + (ch^'0');
        ch  = getchar();
    }
}

int main() {
    ll n ;
    read(n);
    for(int i = 1 ; i <=n ; ++i)
        for(int j = i ; j <= n ; ++j)
            read(c[i][j]);
    return 0;
}