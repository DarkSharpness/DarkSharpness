#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 3;
const int M = 233;
inline int index(int x) { return (x - 1) / M; }


int a[N];
int sum [N / M + 3];
int head[N / M + 3];
int tail[N / M + 3];

inline int length(int x) { return tail[x] - head[x] + 1; }
inline bool check(int x) {  return sum[x] != length(x);  }

void update(int x,int l,int r) {
    for(int i = l ; i <= r ; ++i) {
        int tmp = a[i];
        sum[x] -= (tmp - (a[i] = sqrt(a[i]))); 
    }
}

void add(int l,int r) {
    int x = index(l);
    int y = index(r);
    if(x == y) {
        if(check(x)) update(x,l,r);
    } else {
        if(check(x)) update(x,l,tail[x]);
        if(check(y)) update(y,head[y],r);
        for(int i = x + 1 ; i != y ; ++i)
            if(check(i)) update(i,head[i],tail[i]);
    }
}

void query(int l,int r) {
    int x = index(l);
    int y = index(r);
    int ans = 0;
    if(x == y) {
        if(!check(x)) ans = r - l + 1;
        else for(int i = l ; i <= r ; ++i) ans += a[i];
    } else {
        if(!check(x)) ans += tail[x] - l + 1;
        else for(int i = l ; i <= tail[x] ; ++i) ans += a[i];

        if(!check(y)) ans += r - head[y] + 1;
        else for(int i = head[y] ; i <= r ; ++i) ans += a[i];

        for(int i = x + 1 ; i != y ; ++i) ans += sum[i];
    }
    cout << ans << '\n';
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

    for(int i = index(n) ; i >= 0 ; --i) 
        head[i] = i * M + 1 , tail[i] = (i + 1) * M;
    tail[index(n)] = n;

    while(n--) {
        int opt,l,r,c;
        cin >> opt >> l >> r >> c;
        if(!opt) add(l,r);
        else query(l,r);
    }
    return 0;
}