#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

#define Loop(it,begin,end) for(auto it = begin; it <= end ; ++it)
const int N = 3e5 + 10;
const unsigned int mod = 1e9 + 9;
int a[N],n,m;
inline int M(int x) {
    return x >= mod?
           x - mod : x;
} 
inline int A(int x) {
    return x < 0 ?
           x + mod : x;
}
inline int S(int x) {
    if(x >= mod)   return x - mod;
    else if(x < 0) return x + mod;
    else return x;
}



int pre[N],rfib[N];
inline void prework() {
    pre[1] = 1;
    pre[2] = 2;
    rfib[1] = 1;
    rfib[2] = mod - 1;
    Loop(i,3,n) {
        pre[i]  = S((pre[i-1] << 1) - pre[i-3]);
        rfib[i] = S(rfib[i] - rfib[i]);
    }
}




struct segment_tree {
    struct node {
        int val;
        int tag1,tag2;
    }t[N<<2];
    #define mid ((l+r)>>1)
    #define ls  (id<<1)
    #define rs  (id<<1|1)
    inline void pushup(int id) {
        t[id].val = M(t[ls].val + t[rs].val);
    }
    void pushdown(int id,int l,int r) {
        if(t[id].tag1) {
            t[ls].tag1 = M(t[ls].tag1 + t[id].tag1);
            t[rs].tag1 = M(t[rs].tag1 + t[id].tag1);
            t[ls].val = (t[ls].val + ) 
            t[id].tag1 = 0;
        }
    }
    void build(int id,int l,int r) {
        if(l == r) {
            t[id].val = a[l];
            return;
        }
        build(id, l, mid);
        build(id,mid+1,r);
        pushup(id);
    }
    void update(int id,int l,int r,int L,int R,int tag1,int tag2) {

    }

}t;




int main() {
    scanf("%d%d",&n,&m);
    Loop(i,1,n) {
        scanf("%d%d",a+i);
    }
    t.build(1,1,n);
    return 0;
}