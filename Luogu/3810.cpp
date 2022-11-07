#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long


const int N = 1e5 + 8;
struct node {
    int a,b,c,cnt,sum;
}t[N],s[N];
int n,k;
int ans[N];

inline bool cmp(const node &X,const node &Y) {
    if(X.a != Y.a) return X.a < Y.a;
    if(X.b != Y.b) return X.b < Y.b;
    return X.c < Y.c;
}

inline bool cmp2(const node &X,const node &Y) {
    if(X.b != Y.b)  return X.b < Y.b;
    else  return X.c < Y.c;
}

int dat[N];
inline int lowbit(int x) {
    return x & (-x);
}

inline void add(int x,int v) {
    while(x <= k) {
        dat[x] += v;
        x += lowbit(x);
    }
}
inline int query(int x) {
    int ans = 0;
    while(x) {
        ans += dat[x];
        x -= lowbit(x);
    }
    return ans;
}


void solve(int l,int r) {
    if(l == r) return;
    int mid = (l + r) >> 1;
    solve(l,mid);
    solve(mid+1,r);
    sort(s+l,s+mid+1,cmp2);
    sort(s+mid+1,s+r+1,cmp2);
    int j = l;
    for(int i = mid+1 ; i <= r ; ++i) {
        while(s[i].b >= s[j].b && j <= mid) {
            add(s[j].c,s[j].cnt);
            ++j;
        }
        s[i].sum += query(s[i].c);
    }
    for(int i = l ; i != j ; ++i) {
        add(s[i].c,-s[i].cnt);
    }

}


signed main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for(int i = 1 ; i <= n ; ++i) {
        cin >> t[i].a >> t[i].b >> t[i].c;
    }
    sort(t+1,t+n+1,cmp);
    t[0].a   = -114514;
    t[n+1].a = -114514;
    int m = 0,cnt = 0;
    for(int i = 1 ; i <= n + 1; ++i) {
        if(t[i].a != t[i-1].a ||
           t[i].b != t[i-1].b ||
           t[i].c != t[i-1].c) {
            s[m].cnt = cnt;
            s[++m] = t[i];
            cnt = 0;
        }
        ++cnt;
    }
    --m;
    solve(1,m);
    for(int i = 1 ; i <= m ; ++i) {
        ans[s[i].cnt+s[i].sum-1] += s[i].cnt;
    }
    for(int i = 0 ; i < n ; ++i)
        cout << ans[i] << endl;
    return 0;
}