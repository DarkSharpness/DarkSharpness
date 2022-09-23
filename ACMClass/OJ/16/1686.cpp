#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e6+8;
const int M = 1<<22;
bitset <N> bit;
inline void read(int &tmp) {
    tmp = 0;
    register char ch = getchar();
    while(!isdigit(ch)) ch = getchar();
    while(isdigit(ch)) {
        tmp = (tmp<<1) + (tmp<<3) + (ch^'0') ;
        ch  = getchar();
    }
}

char ch[16];
int TOT=-1;
inline void write(long long tmp) {
    while(tmp) {
        ch[++TOT] = (tmp % 10) ^ '0';
        tmp /= 10;
    }
    while(TOT != -1) {
        putchar(ch[TOT]);
        --TOT;
    }
    putchar('\n');
}

inline void read_bit(int n) {
    char ch = getchar();
    while(!isdigit(ch)) ch = getchar();
    for(int i = 1 ; i <=n ; ++i) {
        bit.set(i,ch != '0');
        ch = getchar();
    }
}


long long Pre[N];

struct segTree {
    private:
    struct node {
        int l,r,cnt,tag;
        long sum;//loc之和
        inline void reverse() {
            cnt  = r - l + 1 -cnt;
            tag ^= 1;
            sum  = Pre[r] - Pre[l-1] - sum;
        }
    }t[M];
    #define ls (id<<1)
    #define rs (id<<1|1)

    //下传标记
    inline void pushdown(int id) {
        if(t[id].tag) {
            t[ls].reverse();
            t[rs].reverse();
            t[id].tag = 0;
        }
    }
    //维护
    inline void pushup(int id) {
        t[id].cnt = t[ls].cnt + t[rs].cnt;
        t[id].sum = t[ls].sum + t[rs].sum;
    }
    void build(int id,int l,int r) {
        t[id].l = l;
        t[id].r = r;
        if(l == r) {
            t[id].cnt = bit[l];
            t[id].sum = bit[l] ? l : 0 ;
            return ;
        }
        build(ls,l,(l+r)>>1);
        build(rs,((l+r)>>1)+1,r);
        pushup(id);
    }
    #define mid ((t[id].l+t[id].r)>>1)
    void reverse(int id,int L,int R) {
        if(t[id].l == L && t[id].r == R) {
            t[id].reverse();
            return ;
        }
        pushdown(id);
        if(R <= mid)     reverse(ls,L,R);
        else if(L > mid) reverse(rs,L,R);
        else {
            reverse(ls, L ,mid);
            reverse(rs,mid+1,R);
        }
        pushup(id);
    }
    int query(int id,int L,int R) {
        if(t[id].l == L && t[id].r == R)
            return t[id].cnt;
        pushdown(id);
        if(R <= mid)     return query(ls,L,R);
        else if(L > mid) return query(rs,L,R);
        else {
            return query(ls, L ,mid)+
                   query(rs,mid+1,R);
        }
    }
    long long queryLoc(int id,int L,int R) {
        if(t[id].l == L && t[id].r == R)
            return t[id].sum;
        pushdown(id);
        if(R <= mid)     return queryLoc(ls,L,R);
        else if(L > mid) return queryLoc(rs,L,R);
        else {
            return queryLoc(ls, L ,mid)+
                   queryLoc(rs,mid+1,R);
        }
    }
    public:
    //建树
    inline void Build(int n) {
        build(1,1,n);
    }
    //查询1的个数
    inline int Query(int L,int R) {
        return query(1,L,R);
    }
    //查询位置的和
    inline long long QueryL(int L,int R) {
        return queryLoc(1,L,R);
    }
    //区间反转
    inline void Reverse(int L,int R) {
        reverse(1,L,R);
    }

}t;

int n,m;

//预处理Pre[i] = i*(i-1) / 2
inline void prework() {
    for(int i = 1 ; i <= n ; ++i) 
        Pre[i] = Pre[i-1] + i;
}

//必定有解
inline void work() {
    /*  线段树
        for(int i = 1 ; i <= n; ++i) 
            cout << t.Query(i,i);
        puts("");
    */
    register int k = n - t.Query(1,n);
    if(!k) {puts("0");return;}
    if(k == n) {write(k);return ;}
    register long long 
        pre1 = (k == 1) ?
                0 : t.QueryL(1,k-1),
        suc0 = t.QueryL(k+1,n);//suc0 = pre1
    suc0 = Pre[n]- Pre[k] - suc0;
    if(!t.Query(k,k))
        write( ((suc0-pre1)<<1) + k );
    else 
        write( ((suc0-pre1)<<1) - k );
}

int main() {
    read(n);
    read(m);
    read_bit(n);
    t.Build(n);
    prework();
    work();
    int l,r;
    while(m--) {
        read(l);
        read(r);
        t.Reverse(l,r);
        work();
    }
    return 0;
}