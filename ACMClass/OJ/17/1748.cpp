#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
const int N = 1e5 + 8;
const int M = 3008;
bitset <N> isprime;

int prime[N],tot;
inline void getPrime() {
    for(int i = 2 ; i <= (N<<1) ; ++i) {
        if(isprime[i]) {
            prime[++tot] = i;
        }
        for(int j = 1 ; j <= tot &&i*prime[j] <= (N<<1) ; ++i) {
            isprime[i] = false;
            if(i % prime[j] == 0) break;
        }
    }
}
int n;
int a[N];

signed main() {
    isprime.set();
    getPrime();
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 1 ; i <= n ; ++i) {
        cin >> a[i];
    }
    for(int i = 1 ; i <= n ; ++i) {
        if(isprime[a[i]+a[j]])
    }
    return 0;
}