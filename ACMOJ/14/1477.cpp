#include<bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

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

auto &read(unsigned char &num)  { return read_u(num); }
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

#ifdef __SIZEO_LONG_DOUBLE__
template <>
void write(long double num) { printf("%Lf",num); }
template <>
void writeline(long double num) { printf("%Lf\n",num); }
#endif

void write() {}
void writeline() { putchar('\n'); }

template <class integer,class ...integers>
void write(const integer &arg,const integers &...args) {
    write(arg);
    putchar(' ');
    write(args...);
}

template <class integer,class ...integers>
void writeline(const integer &arg,const integers &...args) {
    write(arg);
    putchar(' ');
    writeline(args...);
}

}

constexpr ull N = 1e6 + 10;   
// constexpr ull M = 1090000361;
constexpr ull P = (1LL << 31) - 1;
// constexpr ull B = 137;
constexpr ull C = 131;

// ull hash0[N];
ull hash1[N];
// ull base0[N];
ull base1[N];

char ch[N];

int len;
//预处理出str的Hash值
void prework(const char *str) {
    hash1[0] = 
    // hash0[0] = 
    str[0];
    base1[0] = 
    // base0[0] = 
    1;
    int i = 0;
    while(str[++i]) {
        // base0[i] = (base0[i - 1] * B) % M;
        // hash0[i] = (hash0[i - 1] * B + str[i]) % M;
        base1[i] = (base1[i - 1] * C) & P;
        hash1[i] = (hash1[i - 1] * C + str[i]) & P;
    }
    len = i;
    return ;
}

// // Hash0 [l,r]
// ull getHash0(int l,int r) {
//     long long tmp = hash0[r] - hash0[l - 1] * base0[r - l + 1];
//     return tmp >= 0 ? tmp % M : M - (-tmp) % M;
// }

// Hash1 [l,r]
ull getHash1(int l,int r) {
    static ull ans = hash1[r];
    long long tmp = ans - hash1[l - 1] * base1[r - l + 1];
    return tmp & P;
}

int main() {
    scanf("%s",ch);
    prework(ch);
    for(int i = 0 ; i != len - 1 ; ++i)
        if(getHash1(len - 1 - i,len - 1) == hash1[i]) {
            printf("%d\n",i + 1);
        }
    printf("%d",len);
    return 0;
}
