#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


int a[24];
bitset <2048> B;
bitset <1024> C;
bitset <512>  D;
bitset <256> E;
bitset <128> F;
bitset <64>  A;






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

int n,m;
int maxn;
char ch[10];
int tot = 0;

template <class T>
inline void work(T & b) {
    int ans = 0;
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
        if(sum > ans) ans = sum;
    }
    while(ans) {
        ch[++tot] = (ans % 10) ^ '0';
        ans /= 10;
    }
    while(tot) {
        putchar(ch[tot]);
        --tot;
    }

}



int main() {
    read(n,m);
    int tmp = 0;
    for(int i = 0 ; i < n ; ++i) {
        read(a[i]);
        if(tmp < a[i]) tmp = a[i]; 
    }
    c[0] = 0;
    c[1] = 1;
    maxn = 1 << (n-1);
    for(int i = 1 ; i < maxn ; ++i) {
        c[i<<1]   = c[i];    
        c[i<<1|1] = c[i] + 1;
    }
    maxn <<= 1;
    //删除其中m个
    //C (n,m) *(n-m)*n
    int opt = 6;
    tmp *= n;
    while(tmp >= (1<<opt)) ++opt;
    switch(opt) {
        case 7:
            work(F);
            break;
        case 8:
            work(E);
            break;
        case 9:
            work(D);
            break;
        case 10:
            work(C);
            break;
        case 11:
            work(B);
            break;
        default:
            work(A);
    }
    return 0;
}