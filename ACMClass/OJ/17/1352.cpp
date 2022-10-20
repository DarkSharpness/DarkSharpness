#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long


const int N = 10000;




int st[16],top;
int prime[N] = {2,3,5,7,11};
int tot = 5;
inline bool judge(int m) {
    int tmp = sqrt(m);
    for(int i = 3 ; i <= tmp ; i += 2) {
        if(!(m % i)) return false;
    }
    return true;
}

void reverse(int m) {
    top = 0;
    int t = 1;
    int a = m;
    while(a) {
        st[++top] = a % 10;
        a /= 10;
        t *= 10;
    }
    for(int i = 1 ; i <= top ; ++i)
        a = a * 10 + st[i];
    a = a * 10 * t + m;
    for(int i = 0 ; i < 10 ; ++i) {
        if(judge(a)) prime[tot++] = a;
        a += t;
    }
    return;
}
void prework() {
    constexpr int maxn = 1e4;
    for(int i = 1 ; i < maxn ; i += 2)    
        reverse(i);
}

signed main() {
    prework();
    sort(prime,prime+tot);
    prime[tot] = prime[tot-1] + 10;
    int l,r;
    scanf("%d%d",&l,&r);
    l = lower_bound(prime,prime+tot,l)-prime;
    r = upper_bound(prime,prime+tot,r)-prime;
    for(int i = l ; i < r ; ++i)
        printf("%d\n",prime[i]);
    return 0;
}