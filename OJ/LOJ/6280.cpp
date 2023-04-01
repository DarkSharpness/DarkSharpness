#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 3;
const int M = 233;
inline int index(int x) { return (x - 1) / M; }

using ll = long long;

ll a[N];
ll tag[N / M + 3];
ll sum[N / M + 3];
int tail(int x) { return (x + 1) * M; }
int head(int x) {  return x * M + 1;  }


void add(int l,int r,ll c) {
    int x = index(l);
    int y = index(r);
    if(x == y) {
        for(int i = l ; i <= r ; ++i) a[i] += c;
        sum[x] += (r - l + 1) * c;
    } else {
        for(int i = tail(x) ; i >= l ; --i) a[i] += c;
        sum[x] += (tail(x) - l + 1) * c;
        for(int i = head(y) ; i <= r ; ++i) a[i] += c;
        sum[y] += (r - head(y) + 1) * c;
        for(int i = x + 1 ; i != y ; ++i) tag[i] += c,sum[i] += c * M;
    }
}

void query(int l,int r,ll c) {
    int x = index(l);
    int y = index(r);
    ll ans = 0;
    if(x == y) for(int i = l ; i <= r ; ++i) ans += a[i] + tag[x];
    else {
        for(int i = tail(x) ; i >= l ; --i) ans += a[i] + tag[x];
        for(int i = head(y) ; i <= r ; ++i) ans += a[i] + tag[y];
        for(int i = x + 1 ; i != y ; ++i)   ans += sum[i];
    }
    cout << ans % c << '\n';
}


signed main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    int j = 0;
    for(int i = 1 ; i <= n ; ++i) {
        cin >> a[i];
        sum[j] += a[i];
        if(!(i % M)) ++j;
    }
    while(n--) {
        int opt,l,r,c;
        cin >> opt >> l >> r >> c;
        if(!opt) add(l,r,c);
        else query(l,r,c + 1);
    }
    return 0;
}