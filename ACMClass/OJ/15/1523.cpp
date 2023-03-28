#include <iostream>
#include <Dark/inout>

const int N = 5e5 + 3;

#define int long long
signed n,m;
int t[N];
signed a[N];
inline signed lowbit(signed x) { return x & (-x); }

inline void insert(signed x,signed k) 
{ while(x <= n) { t[x] += k; x += lowbit(x); } }
inline int query(signed x) 
{ int sum = 0; while(x) { sum += t[x]; x ^= lowbit(x); } return sum; }
inline void build()  {
    for(signed i = 1 ; i <= n ; ++i) {
        t[i] += a[i] - a[i - 1]; 
        if(i + lowbit(i) <= n) t[i + lowbit(i)] += t[i];
    }
}

signed main() {
    dark::read(n,m);
    char opt;
    for(signed i = 1 ; i <= n ; ++i) dark::read(a[i]);
    build();
    signed x,y,k;
    while(m--) {
        dark::read(opt);
        if(opt == '1') {
            dark::read(x,y,k);
            insert(x , k);
            insert(y + 1, -k);
        } else {
            dark::writeline(query(dark::read(x)));
        }
    }
    return 0;
}
