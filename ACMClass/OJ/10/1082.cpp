#include<bits/stdc++.h>
// #include <Dark/inout>
using namespace std;
const int N = 1e6+10;
int a[N],n,m;
int tail,head,q[N]; 


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

/* Avoid misusage. */
template <class integer>
void write(const integer &) = delete;
/* Avoid misusage. */
template <class integer>
void writeline(const integer &) = delete;

}


void getmin() {
    head = 1 ;
    tail = 0 ;
    for(int i = 1; i <= n; ++i) {
        if(head <= tail && i - q[head] == m) ++head;
        while(head <= tail && a[i] <= a[q[tail]]) --tail;
        q[++tail]=i;
        if(i >= m) dark::write(a[q[head]]),putchar(' ');
    }
}
void getmax() {
    head = 1 ;
    tail = 0 ;
    for(int i = 1; i <= n; ++i) {
        if(head<=tail && i - q[head] == m) ++head;
        while(head <= tail && a[i] >= a[q[tail]]) --tail;
        q[++tail]=i;
        if(i >= m) dark::write(a[q[head]]),putchar(' ');
    }
}

int main() {
    dark::read(n,m);
    for(int i = 1; i <= n ; ++i) dark::read(a[i]);
    getmin();puts("");
    getmax();puts("");
    return 0;
}
