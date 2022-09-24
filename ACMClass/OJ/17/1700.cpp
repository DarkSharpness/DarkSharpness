#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 2008;
/// @brief Fast read-in.
inline void read(int &tmp) {
    static char ch;
    tmp = 0;
    while(!isdigit(ch = getchar()));
    while(isdigit(ch)) {
        tmp = (tmp<<1) + (tmp<<3) + (ch^'0');
        ch  = getchar();
    }
}
struct edge {
    int l,r,v;
    inline bool operator <(const edge & B) {
        return v < B.v;
    }
}e[N * N];
int tot = 0;
struct FwTree {
    private:
    int data[N*N];
    int maxn;
    inline int lowbit(int x) {
        return x&(-x);
    }
    inline void insert(int loc,int val) {
        while(loc <= maxn) {
            data[loc] += val;
            loc += lowbit(loc);
        }
    }
    inline int query(int loc) {
        int ans = 0;
        while(loc) {
            ans += data[loc];
            loc -= lowbit(loc);
        }
        return ans;
    }
    public:
    inline void init(int n) {
        maxn = n;
    }
    inline void Insert(int l,int r) {
        insert( l , 1);
        insert(r+1,-1);
    }
    inline int Query(int l,int r) {
        return query(r)-query(l-1);
    }

}t;


int main() {
    int n ;
    read(n);
    for(int i = 1 ; i <=n ; ++i)
        for(int j = i ; j <= n ; ++j) {
            e[++tot].l;
            e[tot].r;
            read(e[tot].v);
        }
    t.init(n);
    sort(e+1,e+tot+1); 
    int ans = 0;
    for(int i = 1 ; i <= tot ; ++i) {
        int cover = t.Query(e[i].l,e[i].r);
        if(cover < e[i].r - e[i].l +1) {
            t.Insert(e[i].l,e[i].r);
            ans +=
        } 
    }
    return 0;
}