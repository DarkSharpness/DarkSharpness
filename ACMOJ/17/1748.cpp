#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define endl '\n'
constexpr int N = 3008;     // maximum vertex
constexpr int M = 1e5 + 8;  // maximum ai
bitset <M << 1> isprime;// whether a prime
int prime[M],cnt = 0;
inline void getPrime(int maxn) {
    for(int i = 2 ; i <= maxn ; ++i) {
        if(isprime[i]) {
            prime[++cnt] = i;
        }
        for(int j = 1 ; j <= cnt; ++j) {
            if(i * prime[j] >= maxn) break;
            isprime[i * prime[j]] = false;
            if(i % prime[j] == 0) break;
        }
    }
}

struct edge {
    int to,nxt;
}e[N * N >> 1]; // Max : (n/2) * (n/2) * 2
int head[N],tot = 0;
inline void adde(int fr,int to) {
    e[++tot].to = to;
    e[tot].nxt  = head[fr];
    head[fr]    = tot;
}

bitset <N> vis;
int match[N];
int a[N];
/// @brief Search for augmented path.
bool dfs(int id) {
    for(int i = head[id],to ; i ; i = e[i].nxt) {
        if(!vis[to = e[i].to]) {
            vis[to] = true;
            if(!match[to] || dfs(match[to])) {
                match[to] = id;
                return true;
            }
        }
    }
    return false;
}

vector <int> oddd(N);
vector <int> even(N);

signed main() {
    ios::sync_with_stdio(false);
    isprime.set();
    isprime[1] = isprime[0] = false;
    int n;
    cin >> n;
    int maxn = 0;
    for(int i = 1 ; i <= n ; ++i) {
        cin >> a[i];
        if(a[i] > maxn) maxn = a[i];
    }
    getPrime(maxn << 1);
    for(int i = 1 ; i <= n ; ++i) {
        if(a[i] & 1) oddd.push_back(i);
        else         even.push_back(i);
        for(int j = 1 ; j < i ; ++j) {
            if(isprime[a[i]+a[j]]) { // link edge
                adde(i,j);
                adde(j,i);
            }
        }
    }
    if(oddd.size() < even.size()) {
        oddd.swap(even);
    }
    int ans = 0;
    for(auto i : even) {
        vis.reset();
        if(dfs(i)) ++ans;
    }
    cout << n-ans;
    return 0;
}