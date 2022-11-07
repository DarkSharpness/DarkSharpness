#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long
const int N = 2e5 + 8;
int n,k;
int tot;
inline int check(int &id) {
    return id ? id : id = ++tot;
}


struct node {
    int ls,rs,sum;
    node() {
        ls = rs = sum = 0;
    }
}t[N*25];

#define lc t[id].ls
#define rc t[id].rs
#define mid ((l+r) >> 1)
inline void insert(int id,int l,int r,int loc,int val) {
    while(true) {
        t[id].sum += val;
        if(l == r) break;
        if(loc > mid) {
            l = mid + 1;
            id = check(rc);
        } else {
            r = mid;
            id = check(lc);
        }
    }
}

inline int querysum(int id,int l,int r,int loc) {
    int ans = 0;
    while(true) {
        while(id && l != r && loc <= mid) {
            r = mid;
            id = lc;
        }
        if(!id)      return ans;
        if(loc == r) return ans + t[id].sum;
        ans += t[lc].sum;
        l  = mid + 1;
        id = rc;
    }
}

inline int lowbit(int x) {
    return x & (-x);
}

inline void add(int x,int y,int v) {
    while(x <= k) {
        insert(x,1,k,y,v);
        x += lowbit(x);
    }
}

inline int query(int x,int y) {
    int ans = 0;
    while(x != 0) {
        ans += querysum(x,1,k,y);
        x   -= lowbit(x);
    }
    return ans;
}

struct temp {
    int a,b,c;
    inline friend bool operator !=(const temp &A,const temp & B) {
        return A.a != B.a ||
               A.b != B.b ||
               A.c != B.c; 
    }
}s[N];

bool cmp(const temp &X,const temp &Y) {
    if(X.a != Y.a) return X.a < Y.a;
    if(X.b != Y.b) return X.b < Y.b;
    return X.c < Y.c;
}
int sum[N];

signed main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for(int i = 1 ; i <= n ; ++i) {
        cin >> s[i].a >> s[i].b >> s[i].c;
    }
    sort(s+1,s+n+1,cmp);
    int cnt = 0;
    tot = k;
    for(int i = 1 ; i <= n ; ++i) {
        ++cnt;
        if(s[i] != s[i+1]) {
            add(s[i].b,s[i].c,cnt);
            sum[query(s[i].b,s[i].c)-1] += cnt;
            cnt = 0;
        }
    }
    for(int i = 0 ; i < n ; ++i)
        cout << sum[i] << endl;

    return 0;
}