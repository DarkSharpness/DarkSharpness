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

// #define int long long
using ll = long long;
// using ull = unsigned long long;
// using namespace std;
const int N = 2e5 + 3;

class segment_tree {
  private:
    struct node {
        ll sum; /* Sum */
        ll tag; /* Forever tag. */
        node() { sum = tag = 0; }
    } t [N << 2];

    #define ls id << 1
    #define rs id << 1 | 1

    void update(int id,int l,int r,int L,int R,ll val) {
        t[id].sum += (R - L + 1) * val;
        if(l == L && r == R) return (void) (t[id].tag += val);

        int mid = (l + r) >> 1;
        if(R <= mid)     update(ls, l , mid ,L,R,val);
        else if(L > mid) update(rs,mid + 1,r,L,R,val);
        else {
            update(ls, l , mid , L , mid ,val);
            update(rs,mid + 1,r,mid + 1,R,val);
        }
    }
    ll query(int id,int l,int r,int L,int R,ll tag) {
        if(l == L && r == R) return t[id].sum + (R - L + 1) * tag;

        tag += t[id].tag;
        int mid = (l + r) >> 1;
        if(R <= mid)     return query(ls, l , mid ,L,R,tag);
        else if(L > mid) return query(rs,mid + 1,r,L,R,tag);
        else return query(ls, l , mid , L , mid ,tag)
                  + query(rs,mid + 1,r,mid + 1,R,tag);
    }

    #undef ls
    #undef rs

  public:
    int maxn;
    void add(int l,int r,int val) { return update(1,1,maxn,l,r,val); }
    auto sum(int l,int r) { return query(1,1,maxn,l,r,0); }

} T;


struct edge { int nxt,to; } e[N << 1];
int head[N],cnt = 0;
inline void adde(int fr,int to) {
    e[++cnt] = (edge){ head[fr],to }; head[fr] = cnt;
}

int son[N],fat[N],siz[N],dep[N];
void dfs1(int u) {
    int maxsiz = -(siz[u] = 1);
    for(int i = head[u] ; i ; i = e[i].nxt) {
        int v = e[i].to;
        dep[v] = dep[u] + 1;
        dfs1(v);
        siz[u] += siz[v];
        if(siz[v] > maxsiz) maxsiz = siz[son[u] = v];
    }
}

int dfn[N],top[N],tot = 0;
void dfs2(int u,int tp) {
    dfn[u] = ++tot;
    top[u] = tp;
    if(!son[u]) return;
    dfs2(son[u],tp);
    for(int i = head[u] ; i ; i = e[i].nxt) {
        int v = e[i].to;
        if(v == son[u]) continue;
        dfs2(v,v);
    }
}

unsigned root = 1;

void addPath(int x,int y,int val) {
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) std::swap(x,y);
        T.add(dfn[top[x]],dfn[x],val);
        x = fat[top[x]];
    }
    if(dep[x] > dep[y]) std::swap(x,y);
    T.add(dfn[x],dfn[y],val);
}

ll sumPath(int x,int y) {
    ll ans = 0;
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) std::swap(x,y);
        ans += T.sum(dfn[top[x]],dfn[x]);
        x = fat[top[x]];
    }
    if(dep[x] > dep[y]) std::swap(x,y);
    return ans + T.sum(dfn[x],dfn[y]);
}

void addTree(int x,int val) {
    if((unsigned)x == root) { return T.add(1,T.maxn,val); }
    else if(dfn[root] > dfn[x] && dfn[root] < dfn[x] + siz[x]) {
        /* root inside the subtree of x */
        int y = root;
        while(true) {
            // y = fat[top[y]];
            if(top[y] == top[x]) { y = son[x]; break; }
            y = top[y];
            if(fat[y] == x) break;
            y = fat[y];
        }
        T.add(1,T.maxn,val);
        T.add(dfn[y],dfn[y] + siz[y] - 1,-val); /* 逆天,忘记加-了还能过一半的点 */
    } else T.add(dfn[x],dfn[x] + siz[x] - 1,val);
}


signed main() {
    unsigned n;
    T.maxn = dark::read_u(n);
    for(unsigned i = 2,x ; i <= n ; ++i) adde(fat[i] = dark::read(x),i);

    dfs1(root);
    dfs2(root,root);

    unsigned m = dark::read(m);
    unsigned opt,u,v;
    int x;
    while(m--) {
        opt = dark::read(opt);
        if(opt == 1) {
            dark::read(u,x);
            addTree(u,x);
        } else if(opt == 2) {
            dark::read(u,v,x);
            addPath(u,v,x);
        } else if(opt == 3) {
            dark::read(u,v);
            dark::writeline(sumPath(u,v));
        } else {
            dark::read(root);
        }
    }


    return 0;
}
