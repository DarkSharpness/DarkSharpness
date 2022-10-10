#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template <class T>
inline void read(T & tmp) {
    static char ch;
    while(!isdigit(ch = getchar()));
    tmp = 0 ;
    while(isdigit(ch)) {
        tmp = tmp * 10 + (ch ^ '0');
        ch = getchar();
    }
}

constexpr int N = 1e5 + 16;

struct node {
    ll  magic;
    ll  inter;
    bool operator < (const node & B) const{
        return magic > B.magic;
    }
}t[N];

ll highest = 0;

int cnt = -1;

ll b[70];
inline bool Linear_Base(ll x) {
    for(int i = cnt ; i != -1 ; --i) {
        if(x & (1ll << i)) {
            if(!b[i]) {
                b[i] = x;
                return true;
            } else {
                x ^= b[i];
            }
        }
    }
    return false;//xor till 0
}




int main() {
    int n ;
    read(n);
    for(int i = 0 ; i < n ; ++i) {
        read(t[i].inter);
        read(t[i].magic);
        highest = max(highest,t[i].inter);
    }
    sort(t,t+n);
    while(highest) {
        ++cnt;
        highest >>= 1; 
    }
    ll ans = 0;
    int cnt2 = 0;
    for(int i = 0 ; i < n ; ++i) {
        if(Linear_Base(t[i].inter)) {
            ans += t[i].magic;
            ++cnt2;
        }
        if(cnt2 == cnt+1) break;
    }
    printf("%lld",ans);
    return 0;
}