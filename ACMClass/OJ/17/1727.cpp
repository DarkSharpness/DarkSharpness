#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long
const int N = 114514;

int c[N];
int n;
ll p[N]; // prefix sum - capacity
ll f[N]; // prefix sum of p

/**
 * @brief Fast read-in for unsigned integers. \n 
 * Suitable for OIers. 
 * 
 * @param dst The variable to be written into.
 */
template <class T>
inline void read(T &dst) {
    char ch;
    while(!isdigit(ch = getchar()));
    dst = 0;
    while(isdigit(ch)) {
        dst = dst * 10 + (ch ^ '0');
        ch  = getchar();
    }
}
/**
 * @brief Fast read-in for unsigned integers. \n 
 * Suitable for OIers. 
 * 
 */
template <class T>
inline T read() {
    char ch;
    while(!isdigit(ch = getchar()));
    T dst = 0;
    while(isdigit(ch)) {
        dst = dst * 10 + (ch ^ '0');
        ch  = getchar();
    }
    return dst;
}

signed main() {
    read(n);
    p[0] = f[0] = 0;
    for(int i = 1 ; i <= n ; ++i)
        p[i] = p[i-1] + read<int>();
    const ll average = p[n] / n;
    for(int i = 1 ; i <= n ; ++i) 
        p[i] -= average * i;
    sort(p+1,p+n+1);
    for(int i = 1 ; i <= n ; ++i) 
        f[i] = f[i-1] + p[i];
    ll ans = 114514ll << 40;
    for(int i = 1 ; i <= n ; ++i) {
        ll tmp = f[n] - f[i] - p[i] * (n - i * 2 + 1) - f[i-1];
        if(tmp < ans) ans = tmp;
    }
    printf("%lld",ans);
    return 0;
}