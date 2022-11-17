#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long

int rev[16];

signed main() {
    int maxn = 16;
    for(int i=0;i<maxn;i++)
        rev[i]= ( rev[i>>1]>>1 )| ( (i&1) * maxn >> 1 ) ;// 1 << len+1 = maxn
    for(auto i : rev) {
        std::cout << i << ' ';
    }
    return 0;
}