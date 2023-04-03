#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 3;
const int M = 333;

struct node {
    int l,r;
    int val;
    int loc;
} t[N];

void insert()


inline int index(int x) { return (x - 1) / M; }

int a[N];
struct query { int l,r,id; } q[N];




signed main() {
    int n;
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 1 ; i <= n ; ++i) cin >> a[i];
    for(int i = 0 ; i < n ; ++i) {
        int l,r;
        cin >> l >> r;
        q[i] = {l,r,i};
    }
    sort(q,q + n,[](const query &l,const query &r) {
        int x = index(l.l),y = index(r.l);
        if(x != y) return x < y;
        else return (x & 1) ? l.r > r.r : l.r < r.r;
    } );




    return 0;
}