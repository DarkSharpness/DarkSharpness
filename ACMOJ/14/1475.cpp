#include <bits/stdc++.h>
// #include <Dark/inout>


namespace dark {

/* Read a visible char. */
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

const int N = 1e6 + 1;
using ll = long long;
ll pks = 0;

struct president_tree {
    struct node {
        int ls,rs;
        ll val;
    } t[N * 24] ;
    int tot,maxn,i;
    
    struct history {
        int l,r,root;
    } h[N];

    inline void clone(int &id) {
        t[++tot] = t[id];
        id = tot;
    }

    void build(int &id,int l,int r) {
        id = ++tot;
        if(l == r) return (void) (t[id].ls = t[id].rs = t[id].val = 0);        
        int mid = (l + r) >> 1;
        build(t[id].ls, l , mid );
        build(t[id].rs,mid + 1,r);
    }

    void update(int *ptr,int l,int r,int loc,int val) {
        clone(*ptr);
        while(l != r) {
            int mid = (l + r) >> 1;
            if(loc <= mid) { // Go left
                ptr = &(t[*ptr].ls);
                r = mid;
            } else { // Go right
                ptr = &(t[*ptr].rs);
                l = mid + 1;                
            }
            clone(*ptr);
        }
        t[*ptr].val = val;
    }

    ll query(int id,int l,int r,int loc) const {
        while(l != r) {
            int mid = (l + r) >> 1;
            if(loc <= mid) { // Go left
                id = t[id].ls;
                r = mid;
            } else { // Go right
                id = t[id].rs;
                l = mid + 1;                
            }
            return t[id].val;
        }
    }

    inline void init(int n) { h[0].l = h[0].r = 0; return build(h[0].root,1,maxn = n); }
    inline void add(int x,ll val) {
        h[++i] = h[x]; // Move right side of i by 1.
        return update(&(h[i].root),1,maxn,++h[i].r,val);
    }
    inline void remove(int x) {
        h[++i] = h[x];  // Move left side of i by 1.
        /* Remark: mod 2 ^ 32 = no need to do anything. */
        pks = pks * 31 + query(h[i].root,1,maxn,++h[i].l);
    }

    president_tree() : tot(0),i(0) {}
} p ;



signed main() {
    int n = dark::read(n);
    int t = dark::read(t); // type
    p.init(n);
    char opt;
    ll x,y;
    while(n--) {
        dark::read(opt);
        if(opt == '1') {
            dark::read(x,y);
            if(t) x ^= pks, y ^= pks;
            p.add(x,y);
        } else {
            dark::read(x);
            if(t) x ^= pks;
            p.remove(x);
        }
    }
    dark::writeline <unsigned> (pks);
    return 0;
}