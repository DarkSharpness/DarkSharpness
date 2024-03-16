#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline void read(int &tmp) {
    static char ch;
    while(!isdigit(ch = getchar()));
    tmp = 0;
    while(isdigit(ch)) {
        tmp = tmp * 10 + (ch ^ '0');
        ch = getchar();
    }
}

constexpr int N = 1e6 + 8;
int a[N];
int n,m;
unordered_map <int,int> s;
inline ll f(int x) {
    return ll(x)*(x-1) >> 1;
}

int main() {
    read(n);
    read(m);
    s.reserve((n + m)<<1);
    for(int i = 1 ; i <= n ; ++i) {
        read(a[i]);
        a[i] ^= a[i-1];
        ++s[a[i]];
    }
    ++s[0];
    ll sum = 0;
    for(auto iter :s ) {
        sum += f(iter.second);
    }
    int ans1 = 0 ,ans2 = 0;
    ll ans3 = 0;
    ll ans4 = 1ll<<60;
    while(m--) {
        int p,x;
        read(p);
        read(x);
        if(x) {
            --s[a[p]];
            sum -= s[a[p]];
            a[p] ^= x;
            sum += s[a[p]];
            ++s[a[p]];
        }
        ans1 ^= sum;
        if(sum & 1) ++ ans2;
        ans3 = max(ans3,sum);
        ans4 = min(ans4,sum);
    }
    printf("%d\n%d\n%lld\n%lld\n",ans1,ans2,ans3,ans4);
    return 0;
}