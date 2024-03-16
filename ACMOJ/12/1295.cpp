#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


const int N = 1 << 17;
bitset <N> vis;
int prime[N>>2];
int n,tot;
inline void getprime() {
    tot = 0;
    for(int i = 2 ; i <= n ;++i) {
        if(!vis[i]) {
            prime[++tot] = i;
        }
        for(int j = 1 ; j <= tot && prime[j]*i <= n; ++j) {
            vis[prime[j]*i] = true;
            if(i % prime[j] == 0) break;
        }
    }
}
inline void Fread(int &tmp) {
    static char ch;
    tmp = 0;
    while(!isdigit(ch = getchar()));
    while(isdigit(ch)) {
        tmp = tmp * 10 + (ch ^ '0');
        ch = getchar(); 
    }
}

int main() {
    Fread(n);
    if(n >= 30000) puts("0.00000");
    else {
        getprime();
        printf("%lf\n",((double)2.0*tot/n)/n);
    }
    return 0;
}
