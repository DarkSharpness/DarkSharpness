#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 8;

inline int lowbit(int x) {
    return x & (-x);
}

struct FW_tree {
    ll data[N];
    int maxn;
    inline void insert(int loc,int val) {
        while(loc <= maxn) {
            data[loc] += val;
            loc += lowbit(loc);
        }
    }
    inline ll query(int loc) {
        ll ret = 0;
        while(loc) {
            ret += data[loc];
            loc ^= lowbit(loc);
        }
        return ret;
    }
    inline void init(int n) {
        maxn = n;
    }
}t,cnt;
int a[N];
ll pre[N];

inline ll Query(int loc) {
    return t.query(loc);
}
inline ll Querycnt(int l,int r) {
    return cnt.query(r) - cnt.query(l-1);
}
inline void Insert(int loc,int val) {
    t.insert(loc,val);
}
inline void Insertcnt(int loc) {
    cnt.insert(loc,1);
}

inline void read(int &tmp) {
    static char ch;
    while(!isdigit(ch = getchar()));
    tmp = 0;
    while(isdigit(ch)) {
        tmp = tmp * 10 + (ch ^ '0');
        ch = getchar();
    }
}

inline void write(ll tmp) {
    static char ch[24];
    static int tot = 0;
    while(tmp) {
        ch[++tot] = (tmp % 10) ^ '0';
        tmp /= 10;
    }
    while(tot) putchar(ch[tot--]);
    putchar(' ');
}


int main() {
    int n;
    read(n);
    pre[0] = 0;
    int maxn = 0;
    for(int i = 1 ; i <= n ; ++i) {
        read(a[i]);
        pre[i] = pre[i-1] + a[i];
        if(a[i] > maxn) maxn = a[i];
    }
    t.init(maxn);
    cnt.init(maxn);
    ll p = 0;
    for(int i = 1 ; i <= n ; ++i) {
        p += ll(i-1) * a[i] + pre[i-1];
        p -= Query(a[i]);
        int l = a[i];
        for(  ; l <= maxn; l += a[i]) {
            p -= Querycnt(l,maxn) * a[i];
            Insert(l,a[i]);
        }
        Insertcnt(a[i]);
        if(i != 1) {
            write(p);
        }else {
            putchar('0');
            putchar(' ');
        }
    }
    return 0;
}