#include <bits/stdc++.h>
using namespace std;

const int M = 150;
const int N = 5e4 + 3;

// #define int long long

inline int index(int x) { return (x - 1) / M; }

int a[N];
int tag [N / M + 3];
int head[N / M + 3];
int tail[N / M + 3];
int node[N / M + 3][M];
bitset  <N / M + 3> lazy;

inline int find(int x,int c) {
    int len = tail[x] - head[x] + 1;
    if(!lazy[x]) {
        memcpy(node[x],a + head[x],sizeof(int) * len);
        sort(node[x],node[x] + len);
        lazy.set(x);
    }
    return lower_bound(node[x],node[x] + len,c) - node[x];
}

void add(int l,int r,int c) {
    int x = index(l);
    int y = index(r);
    if(x == y) {
        for(int i = l ; i <= r ; ++i) a[i] += c;
        lazy.reset(x);
    } else {
        for(int i = tail[x] ; i >= l ; --i) a[i] += c;
        for(int i = head[y] ; i <= r ; ++i) a[i] += c;
        lazy.reset(x);
        lazy.reset(y);
        for(int i = x + 1 ; i != y ; ++i) tag[i] += c;
    }
}

inline void query(int l,int r,int c) {
    int x = index(l);
    int y = index(r);
    int cnt = 0;
    if(x == y) {
        for(int i = l ; i <= r ; ++i)
            if(a[i] < c - tag[x]) ++cnt;
    } else {
        for(int i = tail[x] ; i >= l ; --i)
            if(a[i] < c - tag[x]) ++cnt;
        for(int i = head[y] ; i <= r ; ++i)
            if(a[i] < c - tag[y]) ++cnt;
        for(int i = x + 1 ; i != y ; ++i)
            cnt += find(i,c - tag[i]);
    }
    cout << cnt << '\n';
}


signed main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i = 1 ; i <= n ; ++i) cin >> a[i];

    for(int i = index(n) ; i >= 0 ; --i)
        head[i] = i * M + 1 , tail[i] = (i + 1) * M;
    tail[index(n)] = n;

    while(n--) {
        int opt,l,r,c;
        cin >> opt >> l >> r >> c;
        if(!opt) add(l,r,c);
        else query(l,r,c * c);
    }
    return 0;
}
