#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 3;
const int M = 230;
inline int index(int x) { return (x - 1) / M; }

int a[N];
int tag[N / M + 3];
int tail(int x) { return (x + 1) * M; }
int head(int x) {  return x * M + 1;  }


void add(int l,int r,int c) {
    int x = index(l);
    int y = index(r);
    if(x == y) for(int i = l ; i <= r ; ++i) a[i] += c;
    else {
        for(int i = tail(x) ; i >= l ; --i) a[i] += c;
        for(int i = x + 1 ; i != y ; ++i) tag[i] += c;
        for(int i = head(y) ; i <= r ; ++i) a[i] += c;
    }
}

inline void query(int r) { cout << a[r] + tag[index(r)] << '\n'; }


signed main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i = 1 ; i <= n ; ++i) cin >> a[i];
    while(n--) {
        int opt,l,r,c;
        cin >> opt >> l >> r >> c;
        if(!opt) add(l,r,c);
        else query(r);
    }
    return 0;
}