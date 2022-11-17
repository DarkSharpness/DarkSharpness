#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long

constexpr static uint64_t mod[2]  = {2281701377,3489660929}; // mod number


ull qpow(ull base,ull pow,ull mod) {
    ull ans = 1;
    while(pow) {
        if(pow & 1) ans = (ans * base) % mod;
        base = (base * base) % mod;
        pow >>= 1;
    }
    return ans;
}

signed main() {
    for(int i = 0 ; i < 22 ; ++i) {
        cout << qpow(3,(mod[1]-1)/(1 << (i+1)),mod[1]) << ",\n";
    }
    cout << '\n';
    for(int i = 0 ; i < 22 ; ++i) {
        cout << qpow((mod[1]+1)/3,(mod[1]-1)/(1 << (i+1)),mod[1]) << ",\n";
    }

    return 0;
}