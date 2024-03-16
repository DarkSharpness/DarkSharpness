#include<bits/stdc++.h>
using namespace std;

// Fast read-in function
inline void read(int &tmp) {
    char ch;
    while(!isdigit(ch = getchar()));
    tmp = 0;
    while(isdigit(ch)) {
        tmp = tmp * 10 + (ch ^'0');
        ch = getchar();
    }
}

const int N = 1e6 + 10;
int f[N];
int n,m;

signed main() {
    read(n);read(m);
    int l,r;
    while(m--) {
        read(l);read(r);
        if(r > l[f]) l[f] = r;
    }
    l = 2,r = *(f+1);
    int maxr = 0,// the maximum right
        cnt  = 1;// count of minimum required intervals
    while(1) {
        if(r == n) {
            printf("%d",cnt); // print out answer
            return 0;
        }
        while(l <= r) {
            if(l[f] > maxr) maxr = l[f];
            ++l;
        }
        if(maxr <= r) {
            puts("-1");// impossible case
            return 0;
        }
        ++cnt;
        r = maxr;
    }
    return 0;
}