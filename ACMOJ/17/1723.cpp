#include<bits/stdc++.h>
#include<bits/stl_algo.h>
using namespace std;
//#define int lont long

int64_t n,m;
int64_t N;
struct node {
    int64_t ls,rs;// left/right son
    int64_t cnt;  // count of elements
    int64_t tag;  // lazy tag
    node() {
        ls = rs = cnt = 0;
    }
};
node t[1919810<<2];
int64_t cnt;

#define lc t[id].ls
#define rc t[id].rs

// dynamic set apply nodes
inline int64_t check(int64_t &t) {
   return (t? t : t = ++cnt);
}

#define mid ((l+r) >> 1)
inline void update(int64_t id,int64_t l,int64_t r,
                              int64_t L,int64_t R) {
    t[id].cnt += R-L+1;
    if(l == L && r == R) {
        ++t[id].tag;
        return;
    }
    if(R <= mid)     update(check(lc),l, mid ,L,R);
    else if(L > mid) update(check(rc),mid+1,r,L,R);
    else {
        update(check(lc),l, mid ,L, mid );
        update(check(rc),mid+1,r,mid+1,R);
    }
}

inline int64_t query(int64_t id,int64_t l,int64_t r,
                                int64_t L,int64_t R) {
    if(!id) return 0; //special case
    if(l == L && r == R) return t[id].cnt;
    if(R <= mid)
        return query(lc,l, mid ,L,R) + t[id].tag * (R - L + 1);
    else if(L > mid)
        return query(rc,mid+1,r,L,R) + t[id].tag * (R - L + 1);
    else return query(lc,l, mid ,L, mid ) +
                query(rc,mid+1,r,mid+1,R) +
                t[id].tag * int64_t(R - L + 1);
}

inline int64_t lowbit(int64_t x) {
    return x&(-x);
}


inline void insert(int64_t loc,int64_t l,int64_t r) {
    while(loc <= N) {
        update(loc,1,n,l,r);
        loc += lowbit(loc);
    }
}


int64_t gettop() {
    int64_t i;
    for(i = 0; (1u << i) <= N ; ++i);
    return i-1;
}

void write(int64_t tmp) {
    if(tmp == 0) {
        puts("0");
        return;
    }
    char ch[16];
    int tot = 0;
    if(tmp < 0) putchar('-'),tmp = -tmp;
    while(tmp) {
        ch[++tot] = (tmp % 10) ^ '0';
        tmp /= 10;
    }
    while(tot) putchar(ch[tot--]);
    putchar('\n');
}


// optimized binary search
// because search 2 ^ x is O(log n) complexity
void search_in(int64_t l,int64_t r,int64_t k) {
    static int64_t top = 1ull << gettop();
    int64_t ans = 0,pre = 0;
    for(int64_t i = top; i != 0 ; i >>= 1) {
        if(ans + i > N) continue;
        int64_t tmp = query(ans+i,1,n,l,r) + pre;
        if(tmp < k) {
            ans += i;
            pre = tmp;
            // prefix cnt 1~ans < k
            // final ans = ans + 1
        }
    }
    write(n-ans);
}

inline void read(int64_t & tmp) {
    char ch;
    bool flag = false;
    while(!isdigit(ch = getchar()))
        if(ch =='-') flag = true;
    tmp = 0;
    while(isdigit(ch)) {
        tmp = tmp * 10 + (ch ^'0');
        ch = getchar();
    }
    if(flag) tmp = -tmp;
}



signed main() {
    read(n);
    read(m);
    cnt = N = n << 1;
    while(m--) {
        int64_t opt,l,r,c;
        read(opt);
        read(l);read(r);
        read(c);
        if(opt == 1) insert(n-c+1,l,r);
        else         search_in(l,r,c);
    }
    return 0;
}