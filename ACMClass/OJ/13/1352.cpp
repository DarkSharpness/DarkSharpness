#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long


const int N = 10000;




int st[8],top;
int prime[N] = {2,3,5,7,11};
int tot = 5;
inline bool judge(int m) {
    int tmp = sqrt(m);
    for(int i = 3 ; i <= tmp ; i += 2) {
        if(!(m % i)) return false;
    }
    return true;
}

int t = 1;
void Reverse(int m,int dep) {
    top = 0;
    int a = m;
    while(a) {
        st[++top] = a % 10;
        a /= 10;
    }
    for(int i = 1 ; i <= dep ; ++i)
        a = a * 10 + st[i];
    a = a * 10 * t + m;
    for(int i = 0 ; i < 10 ; ++i) {
        if(judge(a)) prime[tot++] = a;
        a += t;
    }
    return;
}
void prework() {
    t *= 10;
    memset(st,0,sizeof(st));
    for(int i = 1 ; i < 10 ; i += 2) 
        Reverse(i,1);
    t *= 10;
    memset(st,0,sizeof(st));
    for(int i = 1 ; i < 100 ; i += 2) 
        Reverse(i,2);
    memset(st,0,sizeof(st));
    t *= 10;
    for(int i = 1 ; i < 1000 ; i += 2) 
        Reverse(i,3);
    memset(st,0,sizeof(st));
    t *= 10;
    for(int i = 1 ; i < 10000 ; i += 2) 
        Reverse(i,4);
}

signed main() {
    prework();
    sort(prime,prime+tot);
    int l,r;
    scanf("%d%d",&l,&r);
    l = lower_bound(prime,prime+tot,l)-prime;
    r = upper_bound(prime,prime+tot,r)-prime;
    for(int i = l ; i < r ; ++i)
        printf("%d\n",prime[i]);
    return 0;
}