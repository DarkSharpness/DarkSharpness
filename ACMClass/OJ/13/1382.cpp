#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
template <class T>
inline void Fread(T &arg) {
    static char ch;
    while(!isdigit(ch = getchar()));
    arg = 0;
    while(isdigit(ch)) {
        arg = (arg<<1) + (arg<<3) +(ch ^'0');
        ch = getchar();
    }
}

/*
inline void Fread(int &arg) {
    static char ch;
    static bool fg;
    fg = false;
    while(!isdigit(ch = getchar()))
        if(ch == '-') fg = true;
    arg = 0;
    while(isdigit(ch)) {
        arg = (arg<<1) + (arg<<3) +(ch ^'0');
        ch = getchar();
    }
    if(fg) arg = - arg;
}
*/

inline void read() {}

template<class A,class ...B>
void read(A &arg,B &...args) {
    Fread(arg);
    read(args...);
}

ll y,k,x,p;
ll ans = 0;
int a,n;
__int128_t temp;
//ksm
inline ll ffpow(int base,ll pow) {
    temp = 1;
    while(pow) {
        if(pow & 1) {
            temp *= base;
            temp %= p;   
        }
        temp = base * base;
        base = temp % p;
        pow >>= 1;
    }
    return temp;
}

ll gcd(ll _x,ll _y) {
    if(_y == 0) return _x;
    return gcd(_y,_x%_y);
}

inline void work() {
    static ll tmp = 1;
    if((a-1)%p == 0) {
        ans = (ans+(k+1)) % p;
    } else {
        ans = ans +
            ( (ffpow(y,k+1)-1) *
               ffpow(y-1,k-2) ) %p;
        ans %= p;
    }


    tmp *= x;
    tmp %= p;
}


int main() {
    read(n,x,p);
    ll tmp = 1;
    while(n--) {
        read(a,y,k);
        work();
    }

    return 0;
}