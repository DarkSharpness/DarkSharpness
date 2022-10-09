#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * @brief Fast read-in for unsigned integers. \n 
 * Suitable for OIers. 
 * 
 * @param dst The variable to be written into.
 */
template <class T>
inline void Fread_u(T &dst) {
    static char ch;
    while(!isdigit(ch = getchar()));
    dst = 0;
    while(isdigit(ch)) {
        dst = dst * 10 + (ch ^ '0');
        ch  = getchar();
    }
}

inline void read() {}

/**
 * @brief Read in multiple unsigned integers.
 * 
 */
template <class T,class ...V> 
void read(T &arg,V &...args) {
    Fread_u(arg);
    read(args...);
}
inline void write(int n) {
    static char ch[10];
    static int tot = 0;
    while(n) {
        ch[++tot] = (n % 10) ^ '0';
        n /= 10;
    }
    while(tot) putchar(ch[tot--]);
}


constexpr int N = 1e5 + 8;
int a[N],loc[N],nxt[N],pre[N];
bitset <N> vis;
int n;



int main() {
    read(n);
    for(int i = 0 ; i < n ; ++i) {
        read(a[i]);
        loc[a[i]] = i;
    }
    for(int i = 0 ; i < n ; ++i) {
        pre[i+1] = i;
        nxt[i] = i+1;
    }
    pre[0] = n;
    nxt[n-1] = n;
    for(int i = n ; i >= 1; --i) {
        if(vis[i] || nxt[loc[i]] == n) continue;
        int j = a[nxt[loc[i]]];
        vis[i] = true;
        vis[j] = true;
        write(i);
        putchar(' ');
        write(j);
        putchar(' ');        
        nxt[pre[loc[i]]] = nxt[loc[j]];
        pre[nxt[loc[j]]] = pre[loc[i]]; 
    }
    return 0;
}