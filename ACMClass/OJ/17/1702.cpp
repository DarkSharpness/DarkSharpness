#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

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
    if(!tmp) {
        puts("1");
        return ;
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

const int N = 3e5 + 10;
struct president_tree {
    int length;
    int cnt;
    struct node {
        int ls,rs;
        int cnt;
        inline void copy(const node & src) {
            ls = src.ls;
            rs = src.rs;
            cnt = src.cnt;
        } 
        node() {
        }
    }t[N * 20]; //ÖµÓò½¨Ê÷
    int rt[N];
    int tot;
    #define mid ((l+r) >> 1)

    int build(int l,int r) {
        int root = ++tot;
        if(l == r) return root;
        t[root].ls = build(l , mid);
        t[root].rs = build(mid+1,r);
        return root;
    }

    int update(int id,int l,int r,int loc) {
        int root = ++tot;
        t[root].copy(t[id]);
        ++t[root].cnt;
        if(l == r) return root;
        if(loc <= mid) t[root].ls = update(t[root].ls, l ,mid,loc);
        else           t[root].rs = update(t[root].rs,mid+1,r,loc);
        return root;
    }

    int query(int L,int R,int l,int r,int threshold) const{
        if(l >= r) {
            return t[R].cnt-t[L].cnt;
            //return l;
        }
        int cntL = t[t[R].ls].cnt-t[t[L].ls].cnt,
            cntR = t[t[R].rs].cnt-t[t[L].rs].cnt;
        if(cntL >= threshold) 
            return query(t[L].ls,t[R].ls, l ,mid,threshold);
        if(cntR >= threshold) 
            return query(t[L].rs,t[R].rs,mid+1,r,threshold);
        return 0;
    }

    inline void insert(int loc) {
        rt[cnt+1] = update(rt[cnt],1,length,loc);
        ++cnt;
    }
    inline void init(int n) {
        length = n;
        rt[0] = build(1,length);
    }
    inline int find(int L,int R,int threshold) const{
        return query(rt[L-1],rt[R],1,length,threshold);
    }
    president_tree() {
        cnt = tot = 0;
    }
}t;

int n,q;
int a[N];
int col[N];
int tot = 0;

inline void discretion() {
    for(int i = 1; i <= n ; ++i) {
        if(!col[a[i]]) col[a[i]] = ++tot;
        a[i] = col[a[i]];
    }
}


int main() {
    read(n);
    read(q);
    for(int i = 1 ; i <= n ; ++i)
        read(a[i]);
    discretion();
    t.init(tot);
    for(int i = 1 ; i <= n ; ++i)
        t.insert(a[i]);
    while(q--) {
        int x,y;
        read(x);read(y);
        //write(x);write(y);write(y-x+1);
        int tmp = t.find(x,y,(y-x+2)>>1);
        if(!tmp) puts("1");
        else write((tmp<<1) - (y-x+1));
    }
    return 0;
}