#include <bits/stdc++.h>
using ll = long long;
const int N = 2e5 + 3;
ll v[N];
int a[N],b[N];

int n;
inline int lowbit(int x) { return x & (-x); }

void update(int x) {
    while(x <= n) {
        ++v[x];
        x += lowbit(x);
    }
}

ll query(int x) {
    ll ans = 0;
    while(x <= n) {
        ans += v[x];
        x ^= lowbit(x);
    } return ans;
}

int index(int x) { return std::upper_bound(b,b + n,x) - b; } 

// int find_more(int x) { return b + n - std::lower_bound(b,b + n,x); }

signed main() {
    std::ios::sync_with_stdio(false);
    int x,y;
    std::cin >> n >> x >> y;
    for(int i = 0 ; i < n ; ++i) std::cin >> a[i];
    memcpy(b,0,sizeof(a[0]) * n);
    std::sort(b,b + n);
    long long ans = 0;
    update(index(a[0]));
    for(int i = 1 ; i < n - 1 ; ++i) {
        ll cnt = query(index1);
        update(index(a[i]));

    }
    return 0;
}