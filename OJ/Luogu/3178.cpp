#include <bits/stdc++.h>
// #include <Dark/inout>

namespace dark {

/* Read a signed integer. */
template <class integer>
integer &read_s(integer &num) {
    char ch;
    bool flag = false;
    num = 0;
    while(!isdigit(ch = getchar())) if(ch == '-') flag = true;
    while(isdigit(ch)) {
        num = num * 10 + (ch ^ '0');
        ch  = getchar();
    }
    if(flag) num = -num;
    return num;
}

/* Read an unsigned integer. */
template <class integer>
integer &read_u(integer &num) {
    char ch;
    num = 0;
    while(!isdigit(ch = getchar()));
    while(isdigit(ch)) {
        num = num * 10 + (ch ^ '0');
        ch  = getchar();
    }
    return num;
}


auto &read(signed char  &num)  { return read_s(num); }
auto &read(signed short &num)  { return read_s(num); }
auto &read(signed int   &num)  { return read_s(num); }
auto &read(signed long  &num)  { return read_s(num); }

auto &read(unsigned char  &num) { return read_u(num); }
auto &read(unsigned short &num) { return read_u(num); }
auto &read(unsigned int   &num) { return read_u(num); }
auto &read(unsigned long  &num) { return read_u(num); }

auto &read(signed   long long &num) { return read_s(num); }
auto &read(unsigned long long &num) { return read_u(num); }

#ifdef __SIZEOF_INT128__ /* Special support for int128. */
auto &read(__int128_t &num)  { return read_s(num); }
auto &read(__uint128_t &num) { return read_u(num); }
#endif

auto &read(float &num)  { scanf("%f",&num) ; return num; }
auto &read(double &num) { scanf("%lf",&num); return num; }

#ifdef __SIZEOF_LONG_DOUBLE__
auto &read(long double &num) { scanf("%Lf",&num); return num; }
#endif

template <class integer,class ...integers>
void read_s(integer &arg,integers &...args) { read_s(arg); read_s(args...); }
template <class integer,class ...integers>
void read_u(integer &arg,integers &...args) { read_u(arg); read_u(args...); }
template <class integer,class ...integers>
void read(integer &arg,integers &...args)   { read(arg);   read(args...); }

/* Read one integer of given type. */
template <class integer>
integer read() { integer tmp; return read(tmp); }

/* Write a integer. */
template <class integer>
void write(integer num) {
    if(!num) return (void) putchar('0');
    if(num < 0) num = -num,putchar('-');
    static char ch[3 * sizeof(integer)];
    int top = 0;
    while(num) {
        ch[top++] = '0' ^ (num % 10);
        num /= 10;
    }
    while(top--) putchar(ch[top]);
}

/* Write a integer and change line with \n .*/
template <class integer>
void writeline(integer num) {
    if(!num) return (void) puts("0");
    if(num < 0) num = -num,putchar('-');
    static char ch[3 * sizeof(integer) + 1] = {0};
    int top = 3 * sizeof(integer) - 1;
    while(num) {
        ch[--top] = '0' ^ (num % 10);
        num /= 10;
    }
    puts(ch + top);
}

template <>
void write (char _ch) { putchar(_ch); }
template <>
void writeline (char _ch) { putchar(_ch);putchar('\n'); }

template <>
void write(float num)  { printf("%f" ,num); }
template <>
void writeline(float num)  { printf("%f\n" ,num); }

template <>
void write(double num) { printf("%lf",num); }
template <>
void writeline(double num) { printf("%lf\n",num); }

#ifdef __SIZEOF_LONG_DOUBLE__
template <>
void write(long double num) { printf("%Lf",num); }
template <>
void writeline(long double num) { printf("%Lf\n",num); }
#endif

void write() {}
void writeline() { putchar('\n'); }

/* Write a sequence of integers. */
template <class integer,class ...integers>
void write(const integer &arg,const integers &...args) {
    write(arg);
    putchar(' ');
    write(args...);
}

/* Write a line of integers. */
template <class integer,class ...integers>
void writeline(const integer &arg,const integers &...args) {
    write(arg);
    putchar(' ');
    writeline(args...);
}


/* Read to a range. */
template <class Iterator>
void readRange(Iterator iter,size_t __n) {
    while(__n--) {
        read(*iter);
        ++iter;
    }
}

/* Read to a range [first,last) */
template <class Iterator>
void readRange(Iterator first,Iterator last) {
    while(first != last) {
        read(*first);
        ++first;
    }
}

/* Read to an array. */
template <class integer,size_t __N>
void readRange(integer (&__A)[__N]) {
    for(size_t i = 0 ; i != __N ; ++i)
        read(__A[i]);
}

/* Write a range. */
template <class Iterator>
void writeRange(Iterator iter,size_t __n) {
    if(!__n) return;
    while(--__n) {
        write(*iter);
        putchar(' ');
        ++iter;
    }
    write(*iter);
}

/* Write a range [first,last) . */
template <class Iterator>
void writeRange(Iterator first,Iterator last) {
    if(first == last) return;
    --last;
    while(first != last) {
        write(*first);
        putchar(' ');
        ++first;
    }
    write(*last);
}

/* Write an array. */
template <class integer,size_t __N>
void writeRange(integer (&__A)[__N]) {
    for(size_t i = 0 ; i < __N - 1; ++i)
        write(__A[i]),putchar(' ');
    write(__A[__N - 1]);
}

}

using namespace std;
using ll = long long;
const int N = 1e5 + 3;


int a[N];
int son[N],fat[N],siz[N];
int dfn[N],rev[N],top[N],tot = 0;

struct segment_tree {
    struct node {
        ll sum;
        ll tag;
        node() { sum = tag = 0; }
    } t[N << 2];

    #define ls id << 1
    #define rs id << 1 | 1

    void build(int id,int l,int r) {
        if(l == r) {
            t[id].sum = a[rev[l]];
            return;
        }
        int mid = (l + r) >> 1;
        build(ls, l , mid );
        build(rs,mid + 1,r);
        t[id].sum = t[ls].sum + t[rs].sum;
    }

    void update(int id,int l,int r,int L,int R,ll val) {
        t[id].sum += (R - L + 1) * val;
        if(l == L && r == R) {
            t[id].tag += val;
            return;
        }
        int mid = (l + r) >> 1;
        if(R <= mid)     update(ls, l , mid ,L,R,val);
        else if(L > mid) update(rs,mid + 1,r,L,R,val);
        else {
            update(ls, l , mid , L , mid ,val);
            update(rs,mid + 1,r,mid + 1,R,val);
        }
    }

    ll query(int id,int l,int r,int L,int R,ll tag) {
        if(l == L && r == R) return t[id].sum + tag * (R - L + 1);
        tag += t[id].tag;
        int mid = (l + r) >> 1;
        if(R <= mid)     return query(ls, l , mid ,L,R,tag);
        else if(L > mid) return query(rs,mid + 1,r,L,R,tag);
        else {
            return query(ls, l , mid , L , mid ,tag)
                 + query(rs,mid + 1,r,mid + 1,R,tag);
        }
    }
    #undef ls
    #undef rs
    int maxn;

    void init(int __n) {
        return build(1,1,maxn = __n);
    }
    void add(int l,int r,int val) {
        return update(1,1,maxn,l,r,val);
    }
    ll sum(int l,int r) {
        return query(1,1,maxn,l,r,0);
    }

} T ;

struct edge { int to,nxt; } e[N << 1];
int head[N],cnt = 0;
inline void adde(int fr,int to) {
    e[++cnt] = (edge) {to,head[fr]};
    head[fr] = cnt;
}

void dfs1(int u,int f) {
    siz[u] = 1;
    fat[u] = f;
    for(int i = head[u] ; i ; i = e[i].nxt) {
        int v = e[i].to;
        if(v == f) continue;
        dfs1(v,u);
        siz[u] += siz[v];
        if(siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfs2(int u,int t) {
    rev[dfn[u] = ++tot] = u;
    top[u] = t;
    if(!son[u]) return;
    dfs2(son[u],t);
    for(int i = head[u] ; i ; i = e[i].nxt) {
        int v = e[i].to;
        if(v == son[u] || v == fat[u]) continue;
        dfs2(v,v);
    }
}

inline void addNode(int x,int a) {
    T.add(dfn[x],dfn[x],a);
}

inline void addTree(int x,int a) {
    T.add(dfn[x],dfn[x] + siz[x] - 1,a);
}

inline ll sumPath(int u) {
    ll ans = 0;
    while(top[u] != 1) {
        int v = top[u];
        ans += T.sum(dfn[v],dfn[u]);
        u = fat[v];
    } /* top[u] = 1 and dfn[1] = 1 */
    return ans += T.sum(1,dfn[u]);
}


signed main() {
    int n,m;
    dark::read_u(n,m);
    for(int i = 1 ; i <= n ; ++i) dark::read(a[i]);
    for(int i = 1,x,y ; i < n ; ++i) {
        dark::read_u(x,y);
        adde(x,y);
        adde(y,x);
    }
    dfs1(1,0);
    dfs2(1,1);
    int opt,x,y;
    T.init(n);
    while(m--) {
        dark::read(opt);
        if(opt == 1) {
            dark::read(x,y);
            addNode(x,y);
        } else if(opt == 2) {
            dark::read(x,y);
            addTree(x,y);
        } else {
            dark::writeline(sumPath(dark::read(x)));
        }
    }

    return 0;
}
