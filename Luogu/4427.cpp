#include <bits/stdc++.h>
// #include <Dark/inout>
// #define int long long
using ll = long long;
// using ull = unsigned long long;
using namespace std;

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


constexpr int N = 3e5 + 2;
constexpr int M = 51;
constexpr ll mod = 998244353;

struct edge { int nxt,to; } e[N << 1];
int head[N],cnt = 0;
inline void adde(int fr,int to) {
    e[++cnt] = (edge) { head[fr],to }; head[fr] = cnt;
}

ll sum[N][M];
int fat[N];
int LCA[N];
int expo[N];

namespace Union {

edge E[N << 1];
int Head[N],cnt = 1;
inline void addE(int fr,int to) {
    E[++cnt] = (edge) { Head[fr],to }; Head[fr] = cnt;
}

int anc[N];
/* Find ancestor. */
int get(int x) {
    return anc[x] == x ? x : anc[x] = get(anc[x]);
}

bitset <N> vis;
void tarjan(int u,int dep) {
    vis.set(u);
    anc[u] = u;
    
    {
        ll tmp = dep; /* tmp = dep ^ k */
        for(int k = 1 ; k < M ; ++k) {
            sum[u][k] = (sum[u][k] + tmp) % mod ;
            tmp = (tmp * dep) % mod;
        }
    }

    for(int i = head[u] ; i ; i = e[i].nxt) {
        int v = e[i].to;
        if(vis.test(v)) continue; /* Father case. */
        for(int k = 1 ; k < M ; ++k) sum[v][k] = sum[u][k];
        tarjan(v,dep + 1);
        fat[v] = anc[v] = u;
    }

    for(int i = Head[u] ; i ; i = E[i].nxt) {
        int v = E[i].to;
        if(vis.test(v)) LCA[i >> 1] = get(v);
    }
}

}

using Union::addE;
using Union::E;

signed main() {
    int n = dark::read(n);
    for(int i = 1,x,y; i < n ; ++i) {
        dark::read(x,y);
        adde(x,y); adde(y,x);
    }
    int m = dark::read(m);
    for(int i = 1 ; i <= m ; ++i) {
        int x,y;
        dark::read(x,y,expo[i]);
        addE(x,y); addE(y,x);
    }

    Union::tarjan(1,0);
    for(int i = 1 ; i <= m ; ++i) {
        int x = E[i << 1].to,y = E[i << 1 | 1].to;
        int z = LCA[i],k = expo[i];
        // dark::writeline(z);
        dark::writeline(
            (mod * 2 + sum[x][k] + sum[y][k] - sum[z][k] - sum[fat[z]][k]) % mod
        );
    }
    return 0;
}