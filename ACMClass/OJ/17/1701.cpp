#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

#define Loop(it,begin,end) for(auto it = begin; it <= end ; ++it)
const int N = 3e5 + 10;
const int mod = 1e9 + 9;
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



int pre[N];//fib prefix-sum
int fib[N];//reverse fib
inline void prework() {
    pre[1] = 1;
    pre[2] = 2;
    fib[1] = 1;     
    fib[2] = mod - 1;
    Loop(i,3,n+2) {
        pre[i]  = S((pre[i-1] << 1) - pre[i-3]);
        fib[i]  = A(fib[i-2] - fib[i-1]);
    }
}




struct segment_tree {
    struct node {
        int val;
        int tag1,tag2;//tag1:l ~ r // tag2:l+1 ~ r+1
    }t[N<<2];
    #define mid ((l+r)>>1)
    #define ls  (id<<1)
    #define rs  (id<<1|1)
    inline void pushup(int id) {
        t[id].val = M(t[ls].val + t[rs].val);//checked
    }
    void pushdown(int id,int l,int r) {
        if(!t[id].tag1 && !t[id].tag2) return;
        ll val1 = t[ls].val;
        ll val2 = t[rs].val;
        if(t[id].tag1) {
            t[ls].tag1 = M(t[ls].tag1 + t[id].tag1);
            t[rs].tag1 = M(t[rs].tag1 + t[id].tag1);
            val1 += ll(pre[mid] - pre[l-1] + mod) * t[id].tag1;
            val2 += ll(pre[ r ] - pre[mid] + mod) * t[id].tag1; 
            t[id].tag1 = 0;
        } 
        if(t[id].tag2) { 
            t[ls].tag2 = M(t[ls].tag2 + t[id].tag2);
            t[rs].tag2 = M(t[rs].tag2 + t[id].tag2);
            val1 += ll(pre[mid+1] - pre[ l ] + mod) * t[id].tag2;
            val2 += ll(pre[r+1] - pre[mid+1] + mod) * t[id].tag2;
            t[id].tag2 = 0;
        }
        t[ls].val = val1 % mod;
        t[rs].val = val2 % mod;
    }
    void build(int id,int l,int r) {
        if(l == r) {
            t[id].val = a[l] ;// a[l] <= 1e9 < mod
            return;
        }
        build(ls, l, mid);
        build(rs,mid+1,r);
        pushup(id);
    }
    void update(int id,int l,int r,int L,int R,int tag1,int tag2) {
        if(l == L && r == R) {
            t[id].tag1 = M(t[id].tag1 + tag1);
            t[id].tag2 = M(t[id].tag2 + tag2);
            t[id].val  = (t[id].val + 
                         ll(pre[R] - pre[L-1] + mod) * tag1 +
                         ll(pre[R+1] - pre[L] + mod) * tag2) % mod;
            return;
        } 
        pushdown(id,l,r);
        if(R <= mid)     update(ls,l, mid ,L,R,tag1,tag2);
        else if(L > mid) update(rs,mid+1,r,L,R,tag1,tag2);
        else {
            update(ls,l , mid,L , mid,tag1,tag2);
            update(rs,mid+1,r,mid+1,R,tag1,tag2);
        }
        pushup(id);
    }
    inline int query(int id,int l,int r,int L,int R) {
        if(l == L && r == R) return t[id].val;
        pushdown(id,l,r);
        if(R <= mid) return query(ls, l ,mid,L,R);
        if(L  > mid) return query(rs,mid+1,r,L,R);
        return M(query(ls,l,mid,L,mid) + query(rs,mid+1,r,mid+1,R));   
    }  

}t;

inline void read(int &tmp) {
    static char ch;
    while(!isdigit(ch = getchar()));
    tmp = 0;
    while(isdigit(ch)) {
        tmp = tmp * 10 + (ch ^ '0');
        ch = getchar();
    }
}

inline void write(int tmp) {
    if(tmp == 0) {
        return (void) puts("0");
    } 
    static char ch[20];
    static int tot = 0;
    while(tmp) {
        ch[++tot] = (tmp % 10) ^ '0';
        tmp /= 10;
    }
    while(tot) putchar(ch[tot--]);
    putchar('\n');
}





int main() {
    read(n);
    read(m);
    Loop(i,1,n) {
        read(a[i]);
    }
    t.build(1,1,n);
    prework();
    while(m--) {
        int opt,L,R;
        read(opt);
        read(L);
        read(R);
        if(opt == 1) 
            t.update(1,1,n,L,R,fib[L],fib[L-1]);
        else write(t.query(1,1,n,L,R));
    }
    return 0;
}