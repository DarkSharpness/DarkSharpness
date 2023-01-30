#include <bits/stdc++.h>
// #include <stdint.h>
// #include <Dark/OI>
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

namespace dark {

/**
 * @brief Basic template of segment_tree.
 * 
 * @tparam value_t Inner value_type.
 * @tparam N Length of array(1 - base).
 */
template <class value_t,size_t __N> 
class segment_tree {
  private:
    struct node {
        value_t val; /* Value of the node. */
        value_t tag; /* Forever tag. */
    } data[__N << 2]; /* 4 times at most. */

    const unsigned N; /* Length of inner data. */
    #define ls id << 1
    #define rs id << 1 | 1

    /* Build the segment tree with initial array. */
    void build(value_t *src,unsigned id,unsigned l,unsigned r) {
        data[id].tag = 0;
        if(l == r) {
            data[id].val = src[l];
            return;
        }
        unsigned mid = (l + r) >> 1;
        build(src,ls, l , mid );
        build(src,rs,mid + 1,r);
        data[id].val = data[ls].val + data[rs].val;
    }

    /* Add in a range. Optimized by lifelong tagging. */
    void add(unsigned id,unsigned l,unsigned r,
             unsigned L,unsigned R,value_t val) {
        data[id].val += (R - L + 1) * val;
        if(l == L && r == R) { data[id].tag += val; return; }

        unsigned mid = (l + r) >> 1;
        if(R <= mid)      add(ls, l , mid ,L,R,val);
        else if(L > mid)  add(rs,mid + 1,r,L,R,val);
        else {
            add(ls, l , mid , L , mid ,val);
            add(rs,mid + 1,r,mid + 1,R,val);
        }
    }
    /* Query in a range. Optimized by lifelong tagging. */
    value_t query(unsigned id,unsigned l,unsigned r,
                  unsigned L,unsigned R,value_t tag) const {
        if(l == L && r == R) return data[id].val + (R - L + 1) * tag;

        unsigned mid = (l + r) >> 1;
        tag += data[id].tag;
        if(R <= mid)     return query(ls, l , mid ,L,R,tag);
        else if(L > mid) return query(rs,mid + 1,r,L,R,tag);
        else return query(ls, l , mid , L , mid ,tag)
                  + query(rs,mid + 1,r,mid + 1,R,tag);  
    }
    #undef ls
    #undef rs
  
  public:
    
    /**
     * @brief Build from a given array (1-base).
     * 
     * @param src If src == nullptr,nothing is done.
     */
    void build(value_t *src) { if(src) return build(src,1,1,N); }

    /**
     * @brief Add a value to range [l,r].
     * 
     * @param l The left  side of the range.
     * @param r The right side of the range.
     * @param val The value to be added.
     */
    void update(unsigned l,unsigned r,value_t val) {
        return add(1,1,N,l,r,val);
    }

    /**
     * @brief Query the sum in range [l,r].
     * 
     * @param l The left  side of the range.
     * @param r The right side of the range.
     * @return value_t The sum queryed.
     */
    value_t sum(unsigned l,unsigned r) const {
        return query(1,1,N,l,r,0);
    }

    segment_tree(unsigned length,value_t *src = nullptr) 
        : N(length) {
        // memset(data,0,sizeof(data));
        build(src);
    }

};

}

using namespace dark;


constexpr int N = 1e5 + 3;
long long a[N];

int main() {
    int n,m;
    read_u(n,m);
    for(int i = 1 ; i <= n ; ++i) read_s(a[i]);
    segment_tree <long long,N> t(n,a);
    while(m--) {
        unsigned opt,x,y;
        long long z;
        read(opt,x,y);
        if(opt == 1) {
            read(z);
            t.update(x,y,z);
        } else {
            writeline(t.sum(x,y));
        }
    }
    return 0;
}
