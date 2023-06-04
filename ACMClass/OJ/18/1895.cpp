#include <iostream>
#include <cstring>

// #include <Dark/inout>
#ifndef _DARK_INOUT_H_
#define _DARK_INOUT_H_

#include <locale>
#include <stdio.h>

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

/* Write function part. */

namespace dark {

/* Write a integer. */
template <class integer>
void writeInt(integer num) {
    if(!num) return (void) putchar('0');
    if(num < 0) num = -num , putchar('-');
    static char ch[3 * sizeof(integer)];
    int top = 0;
    while(num) {
        ch[top++] = '0' ^ (num % 10);
        num /= 10;
    }
    while(top--) putchar(ch[top]);
}

/* Write a integer and start a new line.*/
template <class integer>
void writelineInt(integer num) {
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

/* Write an integer */

void write(signed char  num) { writeInt(num); } 
void write(signed short num) { writeInt(num); } 
void write(signed int   num) { writeInt(num); } 
void write(signed long  num) { writeInt(num); } 

void write(unsigned char  num) { writeInt(num); } 
void write(unsigned short num) { writeInt(num); } 
void write(unsigned int   num) { writeInt(num); } 
void write(unsigned long  num) { writeInt(num); } 

void write(signed long long   num) { writeInt(num); }
void write(unsigned long long num) { writeInt(num); }


void writeline(signed char  num) { writelineInt(num); } 
void writeline(signed short num) { writelineInt(num); } 
void writeline(signed int   num) { writelineInt(num); } 
void writeline(signed long  num) { writelineInt(num); } 

void writeline(unsigned char  num) { writelineInt(num); } 
void writeline(unsigned short num) { writelineInt(num); } 
void writeline(unsigned int   num) { writelineInt(num); } 
void writeline(unsigned long  num) { writelineInt(num); } 

void writeline(signed long long   num) { writelineInt(num); }
void writeline(unsigned long long num) { writelineInt(num); }



/* Write a char. */
void write (char _ch) { putchar(_ch); }
/* Write a char and start a new line. */
void writeline (char _ch) { putchar(_ch);putchar('\n'); }

/* Write a string. */
void write(char *__s) { while(*__s) { putchar(*(__s++)); } }
/* Write a string. */
void write(const char *__s) { while(*__s) { putchar(*(__s++)); } }

/* Write a string and start a new line. */
void writeline(char *__s) { puts(__s); }
/* Write a string. */
void writeline(const char *__s) { puts(__s); }


void write(float num)  { printf("%f" ,num); }
void writeline(float num)  { printf("%f\n" ,num); }

void write(double num) { printf("%lf",num); }
void writeline(double num) { printf("%lf\n",num); }

#ifdef __SIZEOF_LONG_DOUBLE__
void write(long double num) { printf("%Lf",num); }
void writeline(long double num) { printf("%Lf\n",num); }
#endif


/* Following is multiple-variable case. */

/* Special case. */

void write() {}
void writeline() { putchar('\n'); }


/* Write a sequence of integers , separated by ' '. */
template <class integer,class ...integers>
void write(const integer &arg,const integers &...args) {
    write(arg);
    putchar(' ');
    write(args...);
}
/* Write a line of integers , separated by ' '. */
template <class integer,class ...integers>
void writeline(const integer &arg,const integers &...args) {
    write(arg);
    putchar(' ');
    writeline(args...);
}

/* Print just one integer. */
template <class integer>
void print(const integer &arg) { write(arg); }

/* Print a sequence of integers without no separation. */
template <class integer,class ...integers>
void print(const integer &arg,const integers &...args) {
    write(arg);
    print(args...);
}

/* Print just one integer and start a new line. */
template <class integer>
void printline(const integer &arg) { writeline(arg); }

/* Print a line of integers without no separation. */
template <class integer,class ...integers>
void printline(const integer &arg,const integers &...args) {
    write(arg);
    printline(args...);
}

/* Avoid misusage. */
template <class integer>
void write(const integer &) = delete;
/* Avoid misusage. */
template <class integer>
void writeline(const integer &) = delete;



}

/* Range related part. */

namespace dark {

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

/* Write a range and start a new line. */
template <class Iterator>
void writelineRange(Iterator iter,size_t __n) {
    if(!__n) return;
    while(--__n) {
        write(*iter);
        putchar(' ');
        ++iter;
    }
    writeline(*iter);
}

/* Write a range [first,last). */
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

/* Write a range [first,last) and start a new line. */
template <class Iterator>
void writelineRange(Iterator first,Iterator last) {
    if(first == last) return;
    --last;
    while(first != last) {
        write(*first);
        putchar(' ');
        ++first;
    }
    writeline(*last);
}

/* Write an array. */
template <class integer,size_t __N>
void writeRange(integer (&__A)[__N]) {
    for(size_t i = 0 ; i < __N - 1; ++i)
        write(__A[i]) , putchar(' ');
    write(__A[__N - 1]);
}

/* Write an array. */
template <class integer,size_t __N>
void writelineRange(integer (&__A)[__N]) {
    for(size_t i = 0 ; i < __N - 1; ++i)
        write(__A[i]) , putchar(' ');
    writeline(__A[__N - 1]);
}

}

#endif


namespace dark {

template <class RandomIt, class Compare>
void slow_sort(RandomIt first,size_t len,Compare comp) {
    for(size_t i = 0 ; i < len ; ++i)
        for(size_t j = 0 ; j < i ; ++j) 
            if(comp(first[i],first[j])) 
                std::swap(first[i],first[j]);
}

template <class RandomIt, class Compare>
void sort(RandomIt first, RandomIt last, Compare comp) {
    size_t len = last - first;
    if(len <= 8) return slow_sort(first,len,comp);
    RandomIt mid = first + rand() % len;
    std::swap(*first,*mid);
    const auto value = *first;
    RandomIt l = first,r = last - 1;
    while(l != r) {
        while(l != r && !comp(*r,value)) --r;
        if(l != r) *l = *r;
        while(l != r && !comp(value,*l)) ++l;
        if(l != r) *r = *l;
    } // now l == r
    *l = value;
    sort(first, l  ,comp);
    sort(l + 1,last,comp);
}


}



const int N = 2e5 + 3;
const int M = 2e5 + 3;
struct query { int fr,to,w,id; } q[N],e[N];
int head[N],tot;
inline void adde(int fr,int to,int w) noexcept
{ e[++tot] = {fr,to,w,head[fr]}; head[fr] = tot; }

namespace fuck{ int qq[M]; }

struct queue {
    int head = 0;
    int tail = 0;
    void push(int x) noexcept
    { fuck::qq[tail++] = x; if(tail == M) tail = 0; }
    int pop() noexcept
    { int x = fuck::qq[head++]; if(head == M) head = 0 ; return x; }
    bool size() const noexcept { return tail != head; }
} Q;

int a[N],c[N],f[N];
bool vis[N],ans[N];
void SPFA_is_dead(int n,int s) {
    memset(f + 1,0x3f,sizeof(f[0]) * n);
    for(int i = 0 ; i < s ; ++i)
        Q.push(c[i]),f[c[i]] = 0,a[c[i]] = c[i],vis[c[i]] = true;
    while(Q.size()) {
        int u = Q.pop();
        for(int i = head[u] ; i ; i = e[i].id) {
            int v = e[i].to;
            int w = e[i].w;
            if(f[u] + w < f[v]) {
                f[v] = f[u] + w;
                a[v] = a[u];
                if(!vis[v]) {
                    vis[v] = true;
                    Q.push(v);
                }
            }
        } vis[u] = false;
    }
}

bool cmp(const query &l,const query &r) noexcept { return l.w < r.w; }

int anc[N];
int find(int x) { return !anc[x] ? x : anc[x] = find(anc[x]); }

void update(int i) {
    int xx = find(e[i].fr);
    int yy = find(e[i].to);
    if(xx != yy) anc[xx] = yy;
}

signed main() {
    int n,s,m;
    srand(time(NULL));
    dark::read(n,s,m);
    for(int i = 0 ; i < s ; ++i) dark::read(c[i]);
    for(int i = 0 ; i < m ; ++i) {
        int u,v,d;
        dark::read(u,v,d);
        adde(u,v,d),adde(v,u,d);
    } SPFA_is_dead(n,s);

    tot = 0;
    for(int i = 0 ; i < m ; ++i) {
        auto [x,y,w,_] = e[i << 1 | 1];
        if(a[x] != a[y]) 
            e[tot++] = {a[x],a[y],f[x] + f[y] + w,0};
    }
    dark::sort(e,e + tot,cmp);
    const int cnt = dark::read <int> ();
    for(int i = 0 ; i < cnt ; ++i)
        dark::read(q[i].fr,q[i].to,q[i].w),q[i].id = i;
    dark::sort(q,q + cnt,cmp);
    for(int i = 0,j = 0 ; i < cnt ; ++i) {
        while(j < tot && e[j].w <= q[i].w) update(j++);
        int x = find(q[i].fr),y = find(q[i].to);
        if(x == y) ans[q[i].id] = true;
    }
    for(int i = 0 ; i < cnt ; ++i)
        puts(ans[i] ? "TAK" : "NIE");
    return 0;
}