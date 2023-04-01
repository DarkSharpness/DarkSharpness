#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 3;
const int M = 332;
const int mod = 10007;
inline int index(int x) { return (x - 1) / M; }

int a[N];
int tag[N / M + 3];
int mul[N / M + 3];
int head[N / M + 3];
int tail[N / M + 3];


void update(int x) {
    if(mul[x] == 1 && tag[x] == 0) return;
    for(int i = head[x] ; i <= tail[x] ; ++i)
        a[i] = (a[i] * mul[x] + tag[x]) % mod;
    mul[x] = 1 , tag[x] = 0;
}

void add(int l,int r,int c) {
    int x = index(l);
    int y = index(r);
    if(x == y) {
        update(x);
        for(int i = l ; i <= r ; ++i) a[i] = (a[i] + c) % mod;
    }
    else {
        update(x);
        for(int i = l ; i <= tail[x] ; ++i) a[i] = (a[i] + c) % mod;
        update(y);
        for(int i = head[y] ; i <= r ; ++i) a[i] = (a[i] + c) % mod;

        for(int i = x + 1 ; i != y ; ++i) tag[i] = (tag[i] + c) % mod;
    }
}

void mult(int l,int r,int c) {
    int x = index(l);
    int y = index(r);
    if(x == y) {
        update(x);
        for(int i = l ; i <= r ; ++i) a[i] = (a[i] * c) % mod;
    } else {
        update(x);
        for(int i = l ; i <= tail[x] ; ++i) a[i] = (a[i] * c) % mod;
        update(y);
        for(int i = head[y] ; i <= r ; ++i) a[i] = (a[i] * c) % mod;

        for(int i = x + 1 ; i != y ; ++i)
            tag[i] = (tag[i] * c) % mod , mul[i] = (mul[i] * c) % mod;
    }
}

inline void query(int x) {
    int t = index(x);
    cout << (a[x] * mul[t] + tag[t]) % mod << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i = 1 ; i <= n ; ++i) { cin >> a[i] ; a[i] %= mod; }

    for(int i = index(n) ; i >= 0 ; --i) 
        head[i] = i * M + 1 , tail[i] = (i + 1) * M , mul[i] = 1;
    tail[index(n)] = n;
    // int m = n;
    while(n--) {
        int opt,l,r,c;
        cin >> opt >> l >> r >> c;
        if(opt == 0) add(l,r,c % mod);
        else if(opt == 1) mult(l,r,c % mod);
        else query(r);
    }
    return 0;
}
