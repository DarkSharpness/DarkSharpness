#include <iostream>
#include <cstring>
#include <Dark/inout>


const int N = 1e5 + 3;

inline int lowbit(int x) { return x & (-x); }

int a[N];
int bak[N];
int data[N];
int r[N];

int max(int p,int q) { return p > q ? p : q; }

signed main() {
    int n;
    dark::read_u(n);
    int m = 0;
    for(int i = 1 ; i <= n ; ++i) {
        m = max(m,dark::read_u(a[i]));
        ++data[a[i]];
    }

    for(int i = 1 ; i <= m ; ++i)
        if(i + lowbit(i) <= m) data[i + lowbit(i)] += data[i];
    memcpy(bak + 1,data + 1,sizeof(int) * m);

    for(int i = 1 ; i <= n ; ++i) {
        int x = a[i];
        while(x) { r[i] += data[x]; x ^= lowbit(x); }
        r[i] = n - i - r[i] + 1;
        x = a[i];
        while(x <= m) { --data[x]; x += lowbit(x); }
    }
    int sum = 0;
    for(int i = n ; i >= 1 ; --i) {
        int x = a[i];
        int l = 0;
        while(x) { l += bak[x]; x ^= lowbit(x); }
        l = i - l;
        if(l > r[i]) std::swap(l,r[i]);
        if(r[i] - (l << 1) > 0) ++sum;
        x = a[i];
        while(x <= m) { --bak[x]; x += lowbit(x);}
    }
    dark::writeline(sum);
    return 0;
}