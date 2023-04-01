#include <bits/stdc++.h>
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
    static char ch[3 * sizeof(integer)] = {0};
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

const int N = 1e5+ 3;
struct segment_tree {
    struct node {
        int tag; /* Tag: 0:nothing | 1:all 0 | 2:all 1  */
        int sum; /* Sum of a node. */
        node() { tag = sum = 0; }
    } t[N << 2];
    int maxn;

    #define ls id << 1
    #define rs id << 1 | 1

    inline void pushup(int id) { t[id].sum = t[ls].sum + t[rs].sum; }
    inline void pushdown(int id,int l,int r,int mid) {
        if(t[id].tag == 1) {
            t[ls].sum = t[rs].sum = 0;
            t[ls].tag = t[rs].tag = 1;
            t[id].tag = 0;
        } else if(t[id].tag == 2) {
            t[ls].sum = mid - l + 1; 
            t[rs].sum = r - mid;
            t[ls].tag = t[rs].tag = 2;
            t[id].tag = 0;
        }
    }

    void update(int id,int l,int r,int L,int R,bool tag) {
        if(l == L && r == R) {
            t[id].sum = tag ? r - l + 1 : 0;
            t[id].tag = tag + 1;
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(id,l,r,mid);
        if(R <= mid)     update(ls, l , mid ,L,R,tag);
        else if(L > mid) update(rs,mid + 1,r,L,R,tag);
        else { /* Update 2 range. */
            update(ls, l , mid , L , mid ,tag);
            update(rs,mid + 1,r,mid + 1,R,tag);
        }
        pushup(id);
    }

    int query(int id,int l,int r,int L,int R) {
        if(l == L && r == R) return t[id].sum;
        int mid = (l + r) >> 1;
        pushdown(id,l,r,mid);
        if(R <= mid)     return query(ls, l , mid ,L,R);
        else if(L > mid) return query(rs,mid + 1,r,L,R);
        else return query(ls, l , mid , L , mid ) 
                  + query(rs,mid + 1,r,mid + 1,R);
    }
    
    void install(int l,int r) {
        return update(1,1,maxn,l,r,true);
    }
    void uninstall(int l,int r) {
        return update(1,1,maxn,l,r,false);
    }

    int sum(int l,int r) {
        return query(1,1,maxn,l,r);
    }

    #undef ls
    #undef rs
}T;

// vector <int> g[N];
struct edge{ int to,nxt; } e[N << 1];
int head[N],cnt = 0;
inline void adde(int fr,int to) {
    e[++cnt] = (edge){to,head[fr]};
    head[fr] = cnt;
}


int fat[N],son[N],dep[N],siz[N];
void dfs1(int u) {
    int maxsiz = 0;
    siz[u] = 1;
    for(int i = head[u] ; i ; i = e[i].nxt) {
        int v = e[i].to;
        dep[v] = dep[u] + 1;
        dfs1(v);
        siz[u] += siz[v];
        if(siz[v] > maxsiz) maxsiz = siz[son[u] = v];
    }
}

int top[N],dfn[N],rev[N],tot = 0;
void dfs2(int u,int first) {
    top[u] = first;
    rev[dfn[u] = ++tot] = u;
    if(!son[u]) return;
    dfs2(son[u],first);
    for(int i = head[u] ; i ; i = e[i].nxt) {
        int v = e[i].to;
        if(v == son[u]) continue;
        dfs2(v,v);
    }
}

/* From u to root. */
void install(int u) {
    int sum1 = T.sum(1,T.maxn);
    while(top[u]) {
        int v = top[u];
        T.install(dfn[v],dfn[u]);
        u = fat[v];
    }  /* Now top[u] = 0*/
    T.install(1,dfn[u]);
    int sum2 = T.sum(1,T.maxn);
    dark::writeline(sum2 - sum1);
}

/* The sub-tree of u. */
void uninstall(int u) {
    int ans = T.sum(dfn[u],dfn[u] + siz[u] - 1);
    dark::writeline(ans);
    T.uninstall(dfn[u],dfn[u] + siz[u] - 1);
}

signed main() {
    int n;
    T.maxn = dark::read(n);
    for(int i = 1 ; i < n ; ++ i) {
        adde(fat[i] = dark::read <unsigned> () , i);
    }
    dep[0] = 0; dfs1(0); dfs2(0,0);
    int m = dark::read_u(m);
    char opt[100];
    while(m--) {
        scanf("%s",opt);
        int x = dark::read_u(x);
        if(opt[0] == 'i') install(x);
        else            uninstall(x);
    }
    return 0;
}
