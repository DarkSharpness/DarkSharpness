#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long
const ll M = 1e9 + 7;


ll C(ll k) {
    return ((k*(k-1))>>1);
}
inline void read(int &tmp) {
    char ch;
    while(!isdigit(ch = getchar()));
    tmp = 0;
    while(isdigit(ch)) {
        tmp = tmp * 10 + (ch ^ '0');
        ch = getchar();
    }

}
const int N = 1e5 + 10;
ll cnt[N];


signed main() {
    int n;
    read(n);
    int len = 0;
    for(int i = 1 ; i <= n ; ++i) {
        int x;
        read(x);
        len = max(len,x);
        ++cnt[x]; 
    }
    ll ans = 0;
    for(int i = 1 ; i <= len ; ++i) {
        ans += C(cnt[i])*C(cnt[i << 1]);
        for(int j = i + 1 ; j <= len ; ++j) {
            ans += cnt[i] *cnt[j] * C(cnt[i+j]);
        }
    }
    printf("%lld",ans % M);

    return 0;
}