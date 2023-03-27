#include <iostream>
#include <cmath>
#include <Dark/inout>

using ll = long long;
const int M = 1000199;
const int N = 1e5 + 1;

struct edge {
    int key;
    int value;
    edge *next;
} e[N];

struct node {
    size_t time = 0;
    edge * next = nullptr;
} data[M];

struct hash_map {
    size_t cnt =  1;
    size_t tot = -1;

    void insert(int key,int value) {
        const int index = key % M;
        if(data[index].time != cnt) data[index] = {cnt,nullptr};
        data[index].next = &(e[++tot] = {key,value,data[index].next});
    }

    void clear() { ++cnt; tot = -1; }

    edge *find(int key) {
        const int index = key % M;
        if(data[index].time != cnt) return nullptr;
        edge *cur = data[index].next;
        while(cur) {
            if(cur->key == key) return cur;
            cur = cur->next;
        }
        return nullptr;
    }
} m ;


ll fast_pow(ll base,ll t,const ll p) {
    ll ans = 1;
    while(t) {
        if(t & 1) ans = (ans * base) % p;
        base = (base * base) % p;
        t >>= 1;
    }
    return ans;
}

ll inverse;  // inverse of y
ll s;        // block size

ll inv(ll x,const ll p) { return fast_pow(x,p - 2,p); }

ll work_r(ll cur,ll g,ll p) {
    const ll base = fast_pow(g,s,p);
    for(int i = 1 ;  ; ++i) {
        auto iter = m.find(cur = (cur * base) % p);
        if(iter) return i * s - iter->value;
    }
}

ll prework(const ll p,ll g,ll y) {
    s = sqrt(p);
    m.clear();
    ll cur = 1;
    for(int i = 0 ; i < s; ++i)
        m.insert(cur,i) , cur = (cur * g) % p;
    return work_r(inv(y,p),g,p) % p;
}

signed main() {
    ll Q = dark::read(Q);
    // freopen("tmp.txt","w",stdout);
    while(Q--) {
        ll q,g,y,t,p;
        dark::read(q,g,y,t);
        p = q << 1 | 1;
        ll x = prework(p,g,y);
        while(t--) {
            ll c1,c2;
            dark::read(c1,c2);
            dark::write((c2 * fast_pow(inv(c1,p),x,p)) % p);
            putchar(t ? ' ' : '\n');
        }
    }
    return 0;
}
