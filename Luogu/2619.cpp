#include <bits/stdc++.h>
// #include <Dark/inout>
/* Read function part. */

namespace dark {

/* Read a visible char. (Using standard ASCII.) */
char &read_char(char &ch) {
    do { ch = getchar(); } while(ch > 126 || ch < 33);
    return ch;
}

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

/* Special case : read a visible char. */
auto &read(char &ch) { return read_char(ch); }

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

/* Read a visible string. (Using standard ASCII.) */
char *read(char *str) { 
    do { *str   = getchar(); } while(*str > 126 || *str < 33); 
    do { *++str = getchar(); } while(*str > 32 && *str < 127);
    *str = '\0';
    return str;
}


/* Read in a sequence of integers. */
template <class integer,class ...integers>
void read_s(integer &arg,integers &...args) { read_s(arg); read_s(args...); }
/* Read in a sequence of integers. */
template <class integer,class ...integers>
void read_u(integer &arg,integers &...args) { read_u(arg); read_u(args...); }
/* Read in a sequence of integers. */
template <class integer,class ...integers>
void read(integer &arg,integers &...args)   { read(arg);   read(args...); }



/* Paramless version. */


/* Read an integer any given type. */
template <class integer>
integer read() { integer tmp; return read(tmp); }
/* Read an unsigned integer of given type. */
template <class integer>
integer read_u() { integer tmp; return read_u(tmp); }
/* Read a signed integer of given type. */
template <class integer>
integer read_s() { integer tmp; return read_s(tmp); }
/* Read a visible char. */
char read_char() { char tmp; return read_char(tmp); }

/* Avoid misusage. */
template <class integer>
void read(integer &arg) = delete;

}

using namespace std;

const int N = 1e6 + 10;
int anc[N];

struct edge {
    int x,y,w;
} b[N],w[N];
int topb = 0,topw = 0;

inline bool cmp(const edge &l,const edge &r) 
noexcept { return l.w < r.w; }

int find(int x) noexcept
{ return anc[x] == x ? x : (anc[x] = find(anc[x])); }

int head[2][102];
struct Edge { int nxt; edge e; } e[N + 200];
int tot = 0;

inline void adde(int x,int y,int t,bool c) {
    e[++tot] = Edge { head[c][t] , { x,y,t } };
    head[c][t] = tot;
}

signed main() {
    int n,m,k;
    dark::read_u(n,m,k);

    for(int i = 0 ; i < m ; ++i) {
        int x,y,t;
        dark::read_u(x,y,t);
        char ch = dark::read_char(ch);
        adde(x,y,t,ch == '1');
    }

    for(int i = 0 ; i < 101 ; ++i)
        for(int j = head[0][i] ; j ; j = e[j].nxt)
            w[topw++] = e[j].e;
    w[topw].w = 1919810;

    for(int i = 0 ; i < 101 ; ++i)
        for(int j = head[1][i] ; j ; j = e[j].nxt)
            b[topb++] = e[j].e;
    b[topb].w = 114514;

    int l = -103 , r = 103;
    int mid = 0;
    int ans = 191981000;

    while(l != r) { // At most limited times
        mid = (l + r) >> 1;
        std::iota(anc , anc + n , 0);
        int sum = 0;
        int i = 0;  // black front
        int j = 0;  // white front
        int wcnt = 0;
        int cnt = 1;
        while(cnt != n) {
            edge *ptr = (b[i].w < w[j].w + mid) ? &b[i++] : &w[j++];
            int x = find(ptr->x);
            int y = find(ptr->y);
            if(x == y) continue;
            sum  += ptr->w;
            wcnt += (unsigned(ptr - w) < unsigned(topw));
            anc[x] = y;
            ++cnt;
        }
        if(wcnt >= k) { l = mid + 1; ans = sum + (wcnt - k) * mid; }
        else r = mid;
    }
    printf("%d",ans);
    return 0;
}
