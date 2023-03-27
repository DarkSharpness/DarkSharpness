#include <bits/stdc++.h>
#include <Dark/inout>


using namespace std;
using ll = long long;
constexpr int N = 5e4 + 9;
ll ans[N];
ll a[N];
ll bucket[N];

struct node {
    int l,r,i;
} q[N];

constexpr int sqr = 400;
inline int index(int x) { return (x - 1) / sqr; }

inline bool cmp(const node &x,const node &y) {
    int w = index(x.l),z = index(y.l);
    if(w != z) return w < z;
    return w & 1 ? x.r > y.r : x.r < y.r; 
}

ll sum = 0;
inline void add(int x) { sum += 2 * (bucket[x]++) + 1; }
inline void del(int x) { sum -= 2 * (bucket[x]--) - 1; }


signed main() {
    int n,m,k;
    dark::read(n,m,k);
    for(int i = 1 ; i <= n ; ++i) dark::read(a[i]);
    for(int i = 0 ; i < m ; ++i) dark::read(q[i].l,q[i].r),q[i].i = i;
    sort(q,q + m,cmp);
    int l = 1,r = 0; // range [l,r]
    for(int i = 0 ; i < m ; ++i) {
        while(r < q[i].r) add(a[++r]);
        while(l > q[i].l) add(a[--l]);
        while(r > q[i].r) del(a[r--]);
        while(l < q[i].l) del(a[l++]);
        ans[q[i].i] = sum;
    }
    for(int i = 0 ; i < m ; ++i) dark::writeline(ans[i]);
    return 0;
}