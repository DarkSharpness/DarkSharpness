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

// #include <Dark/memleak>
// #include <Dark/Container/heap.h>

namespace dark {

constexpr size_t HEADER_OF_HEAP = 0;

template <class value_t>
struct heap_node {
    size_t dist;
    heap_node *ls;
    heap_node *rs;
    value_t val;
    template <class ...Args>
    heap_node(size_t _d,heap_node *_l,heap_node *_r,Args &&...objs):
        dist(_d),ls(_l),rs(_r),
        val(std::forward <Args> (objs)...) {}
    ~heap_node() = default;
};

using value_t = size_t;

struct heap_allocator :
    public std::allocator <heap_node <value_t>>,
    protected std::vector <heap_node <value_t>*> 
{
    using node   = heap_node <value_t>;
    using vector = std::vector <node *>;
    using _Alloc = std::allocator <node> ;

    heap_allocator() = default;
    heap_allocator(heap_allocator &&) noexcept = default;
    heap_allocator(const heap_allocator &) noexcept {}

    /* Reserve the one with bigger memory. */
    heap_allocator &operator = (heap_allocator &&rhs) noexcept {
        if(this != &rhs && vector::size() < rhs.vector::size()) {
            vector::operator = (std::move(rhs));
        }
        return *this;
    }
    /* Do nothing */
    heap_allocator &operator = (const heap_allocator &) noexcept { return *this; }


    /* Allocate only one node. */
    node *allocate(size_t __n) {
        if(empty()) return _Alloc::allocate(1);
        else {
            node *ptr = vector::back();
            vector::pop_back();
            return ptr;
        }
    }

    /* Deallocate only one node. */
    void deallocate(node *ptr,size_t __n) {
        vector::push_back(ptr);
    }

    ~heap_allocator() {
        for(auto ptr : *this) _Alloc::deallocate(ptr,1);   
    }
};

constexpr size_t __N = sizeof(heap_allocator);

class heap : protected heap_allocator {
  public:
    using node = heap_node <value_t>;
    using allocator = heap_allocator;

  protected:

    /* Special node with its distance as exactly 0. */
    static node *const null;
    node *root;
    size_t count;


    /* Merge 2 nodes. */
    static node *merge(node *x,node *y) {
        if(x == null) return y;
        if(y == null) return x;
        if(y->val < x->val) std::swap(x,y); // Smaller
        x->rs = merge(x->rs,y);
        if(x->ls->dist < x->rs->dist)
            std::swap(x->ls,x->rs);
        x->dist = x->rs->dist + 1;
        return x;
    }


    /* Alloc one element and construct it. */
    template <class ...Args>
    node *alloc(size_t dist,node *ls,node *rs,Args &&...objs) {
        node *temp = this->allocate(1);
        this->construct(temp,dist,ls,rs,std::forward <Args> (objs)...);
        return temp;
    }


    /* Dealloc one element. */
    void dealloc(node *temp) {
        this->destroy(temp);
        this->deallocate(temp,1);
    }


    /* Copy node info from target. */
    node *copy(node *target) {
        if(target == null) return null;
        return alloc(target->dist,
                    copy(target->ls),
                    copy(target->rs),
                    target->val);
    }


    /* Remove the node. */
    void remove(node *target) {
        if(target == null) return;
        remove(target->ls);
        remove(target->rs);
        dealloc(target);
    }

  public:
    /* Emptized. */
    heap() noexcept : root(null),count(0) {}

    /* Move content. */
    heap(heap &&rhs) noexcept : allocator(std::move(rhs)) {
        root      = rhs.root;
        count     = rhs.count;
        rhs.root  = null;
        rhs.count = 0;
    }

    /* Copy content. */
    heap(const heap &rhs) : allocator(rhs) {
        root  = copy(rhs.root);
        count = rhs.count; 
    }

    /* Removal. */
    ~heap() noexcept {
        if(root == null) return;
        remove(root);
        count = 0;
    }

    /* Move content. */
    heap &operator = (heap &&rhs) noexcept {
        if(this != &rhs) {
            this->~heap();
            this->construct(this,std::move(rhs));
        }
        return *this;
    }
    /* Copy content. */
    heap &operator = (const heap &rhs) {
        if(this != &rhs) {
            this->~heap();
            this->construct(this,rhs);
        }
        return *this;
    }


    /* Return const reference to the smallest element. */
    const value_t &top() const { return root->val; }

    /* Push one element to the heap. */
    template <class ...Args>
    void push(Args &&...objs) {
        ++count;
        root = merge(root,alloc(1,null,null,std::forward <Args> (objs)...));
    }

    /* Pop out the top element. */
    void pop() {
        if(root == null) return;
        --count;
        node *temp = root;
        root = merge(root->ls,root->rs);
        dealloc(temp);
    }

    bool empty()  const noexcept { return count; }
    size_t size() const noexcept { return count; }

};


heap::node *const heap::null = (heap::node *)(&HEADER_OF_HEAP);

}


signed main() {
    dark::heap x;
    int n = dark::read <int> ();
    while(n--) {
        char opt = dark::read_char();
        if(opt == '1') {
            x.push(dark::read <size_t> ());
        } else if(opt == '2') {
            dark::writeline(x.top());
        } else if(opt == '3') {
            x.pop();
        } else break;
    }

    return 0;
}
