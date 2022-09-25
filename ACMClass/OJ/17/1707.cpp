#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


int a[24];
bitset <2048> b;
int c[1<<20]; //一的个数

template <class T>
inline void ffread(T &tmp) {
    static char ch;
    tmp = 0;
    while(!isdigit(ch = getchar()));
    while(isdigit(ch)) {
        tmp = tmp * 10 + (ch^'0');
        ch = getchar();
    }
}

//终点
inline void read() {}


template <class T,class ...V>
void read(T &arg,V& ...args) {
    ffread(arg);
    read(args...);
}


int main() {
    int n,m;
    read(n,m);
    for(int i = 0 ; i < n ; ++i) read(a[i]);
    c[0] = 0;
    c[1] = 1;
    int maxn = 1 << (n-1);
    for(int i = 1 ; i < maxn ; ++i) {
        c[i<<1]   = c[i];    
        c[i<<1|1] = c[i] + 1;
    }
    maxn <<= 1;
    int ans = 0;
    //删除其中m个
    //C (n,m) *(n-m)*n
    for(int i = (1<<m)-1 ; i < maxn ; ++i) {
        if(c[i] != m) continue;
        b.reset();
        int tmp = 0;
        b[0] = true;
        for(int j = 0; j < n ; ++j) {
            if(! (i & (1<<j)) ) {
                tmp += a[j];
                b |= (b << a[j]);
            } 
        }
        int sum = 0;
        for(int j = 1; j <= tmp ; ++j)
            if(b[j]) ++sum;
        ans = max(ans,sum);
    }
    printf("%d",ans);
    return 0;
}