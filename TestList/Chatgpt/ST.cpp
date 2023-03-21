#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 16;
const int M = 2e6 + 16;
int f[18][N];
int Log[N];

inline void Fread(int &tmp){
    char ch;
    tmp = 0;
    while(!isdigit(ch = getchar()));
    while(isdigit(ch)) {
        tmp = (tmp<<1) + (tmp<<3) + (ch^'0');
        ch = getchar();
    }
}


inline void read(){}

template <class T,class ...V>
void read(T &arg,V& ...args) {
    Fread(arg);
    read(args...);
}

int n,m;
inline void work() {
    Log[1] = 0;
    for(int i = 2 ; i <=n ; ++i) 
        Log[i] = Log[i>>1] +1;
    for(int j = 2 ; j <= n; j <<= 1) {//区间长度
        for(int l = 1 ; l <= n-j+1 ; ++l) {//区间左端点
            int k = Log[j];//
            f[k][l] = max(f[k-1][l],
                          f[k-1][l+(j>>1)]
                          );
            //cout << f[k][l] << ' ';
        }
        //puts("");
    }

}

inline void write(int tmp) {
    if(!tmp) {
        puts("0");
        return ;
    }
    static char ch[16];
    static int tot = 0;
    while(tmp) {
        ch[++tot] = '0' ^ (tmp%10);
        tmp/=10;
    }
    while(tot) 
        putchar(ch[tot--]);
    putchar('\n');
}


inline int Get(int l,int r) {
    int k = Log[r-l+1]; // r-l+1 
    // (1 << k+1) > n 
    return max(f[k][l],f[k][r-(1<<k)+1]);
}

int main() {
    read(n,m);
    for(int i = 1 ; i <=n ; ++i) 
        read(f[0][i]);
    work();
    int l,r;
    while(m--) {
        read(l,r);
        write(Get(l,r));
    }
    return 0;
}