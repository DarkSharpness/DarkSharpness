#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 2e5+8;

struct FwTree {
    private:
    struct node{
        int cnt;
        ll  sum;
        ll operator*(const node &B) {
            cnt -= B.cnt;
            sum -= B.sum;
            return cnt*sum;
        }
        node(int Cnt,ll Sum) {
            cnt = Cnt;
            sum = Sum;
        }
    };
    int maxn;
    ll sum[N];
    int cnt[N];
    inline int lowbit(int x) {
        return x&(-x);
    }
    
    inline node query(int loc) {
        int Cnt = 0;
        ll  Sum = 0;
        while(loc) {
            Cnt += cnt[loc];
            Sum += sum[loc]; 
            loc -= lowbit(loc);
        }
        return node(Cnt,Sum);
    }
    public:
    inline void insert(int loc,int val) {
        while(loc <= maxn) {
            sum[loc] += val;
            ++cnt[loc];
            loc += lowbit(loc);
        }
    } 
    inline void remove(int loc,int val) {
        while(loc <= maxn) {
            sum[loc] -= val;
            --cnt[loc];
            loc += lowbit(loc);
        }
    }
    inline ll query(int l,int r) {
        return query(r)*query(l-1);
    }
    inline void set(int n) {
        maxn = n;
    }

}t;
int n,m;
ll s;
struct node {
    int w;
    int v;
    int loc;
    inline bool operator <(const node& B) const{
        return w < B.w;
    }
    node(int W,int V,int L) {
        w = W;
        v = V;
        loc = L;
    }
    node() {
        
    }
}p[N];
int first[N];
int tot ;

inline void discrete() {
    sort(p+1,p+n+1);
    ++n;//开新的节点
    p[n] = node{p[n-1].w+1,0,n};
    tot = 0;
    for(int i = 1,tmp = 0; i <=n ; ++i) {
        if(p[i].w != tmp) {
            ++tot;
            first[tot] = i; 
            tmp = p[i].w;
        }
        p[i].w = tot;
    }
    /*
    */
}

inline void Search() {
    int l = 1  ;
    int r = tot;
    int last = tot;
        

}



int main() {
    scanf("%d%d%lld",&n,&m,&s);
    for(int i = 1 ; i <=n ; ++i) {
        scanf("%d%d",&p[i].w,&p[i].v);
    }
    discrete();
    Search();
    return 0;
}