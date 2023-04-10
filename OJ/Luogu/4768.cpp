#include<iostream>
#include<cmath>
#include<cstring>

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

namespace dark {



template <class value_t,class Compare = std::less <value_t> >
class heap {
  private:
    struct node;
    struct implement;
    using pointer = node *;

    struct node {
        pointer ls;
        pointer rs;
        size_t dist;
        value_t val;

        template <class ...Args>
        node(pointer _l,pointer _r,size_t _d,Args &&...objs)
            : ls(_l),rs(_r),dist(_d),
              val(std::forward <Args> (objs)...) {}
    };

    struct implement : std::allocator <node> , Compare {
        size_t count;   /* Count of all the elements. */

        implement() noexcept : count(0) {}

        template <class ...Args>
        pointer alloc(pointer __l,pointer __r,size_t __d,Args &&...objs) {
            ++count;
            pointer __p = this->allocate(1);
            this->construct(__p,__l,__r,__d,std::forward <Args> (objs)...);
            return __p;
        }

        void dealloc(pointer __p) {
            --count;
            this->destroy(__p);
            this->deallocate(__p,1);
        }

    };

    pointer   root;    /* Root node of the tree. */
    implement impl;

    /* Merge 2 nodes x and y. */
    pointer merge(pointer x,pointer y) {
        if(!x) return y;
        if(!y) return x;
        /* Now x and y are not empty. */

        if(impl(y->val,x->val)) std::swap(x,y); // Smaller as x
        x->rs = merge(x->rs,y); // Merge shorter rs with y.

        if(!x->ls || x->ls->dist < x->rs->dist)
            std::swap(x->ls,x->rs); // ls should be longer than rs

        x->dist = x->rs ? x->rs->dist + 1 : 1;
        return x;
    }

    /* Copy node info from target node. */
    pointer copy(pointer target) {
        if(!target) return nullptr;
        return impl.alloc(copy(target->ls),copy(target->rs),target->dist,target->val);
    }

    /* Remove target node with its sub-tree.(No destruction.) */
    void remove(pointer target) {
        if(!target) return;
        remove(target->ls);
        remove(target->rs);
        impl.dealloc(target);
    }

  public:

    /* Emptized. */
    heap() noexcept : root(nullptr) {}
    /* Copy content. */
    heap(const heap &rhs) : root(copy(rhs.root)) {}

    /* Move content. */
    heap(heap &&rhs) noexcept : root(rhs.root),impl(rhs.impl) 
    { rhs.root = nullptr; rhs.impl.count = 0; }

    /* Now heap is re-initialized to empty. */
    ~heap() noexcept { clear(); }

    /* Copy content. */
    heap &operator = (const heap &rhs) {
        if(this != &rhs) {
            clear(); /* Recycle nodes. */
            root = copy(rhs.root);
        }
        return *this;
    }

    /* Move content. */
    heap &operator = (heap &&rhs) noexcept {
        if(this != &rhs) {
            clear(); /* Recycle nodes. */
            std::swap(root,rhs.root);
        }
        return *this;
    }

    /* Clean all the elements. */
    void clear() noexcept { remove(root); root = nullptr; }

    /* Return const reference to the smallest element. */
    const value_t &top() const { return root->val; }

    /* Push one element to the heap. */
    template <class ...Args>
    void emplace(Args &&...objs) {
        root = merge(root,impl.alloc(nullptr,nullptr,1,std::forward <Args> (objs)...));
    }

    /* Push one element to the heap. */
    void push(value_t &&obj) {
        root = merge(root,impl.alloc(nullptr,nullptr,1,std::move(obj)));
    }

    /* Push one element to the heap. */
    void push(const value_t &obj) {
        root = merge(root,impl.alloc(nullptr,nullptr,1,obj));
    }

    /* Pop out the top element. */
    void pop() {
        if(!root) return; /* Empty tree. */
        pointer temp = root;
        root = merge(root->ls,root->rs);
        impl.dealloc(temp);
    }

    /* Merge 2 heaps. */
    void merge(heap &rhs) {
        root = merge(root,rhs.root);
        impl.count += rhs.size();
        rhs.root = nullptr;
        rhs.impl.count = 0;
    }

    bool empty()  const noexcept { return !root; }
    size_t size() const noexcept { return impl.count; }

};


}

// #define int long long
using namespace std;

const int N = 800010;
int n,m,Q,K,S;

struct edge { int u,v,h; } e[N << 1],E[N << 1];
bool cmp(const edge &a,const edge &b){ return a.h > b.h; }
int head[N],tot,cnt;

int h[N];
int dis[N];
int fat[23][N];
int anc[N];
int minn[N];
bool vis[N];
dark::heap <pair<int,int>> q;

inline void adde(int u,int v,int d)
{ E[++tot] = {head[u],v,d}; head[u] = tot; }
int find(int x)
{ return x == anc[x] ? x : anc[x] = find(anc[x]); }


void dijkstra() {
    memset(vis, 0 ,sizeof(vis));
    memset(dis,120,sizeof(dis)); 
    dis[1] = 0;
    q.emplace(0,1);
    while(!q.empty()) {
        int u = q.top().second;
        q.pop();
        if(vis[u]) continue;
        vis[u] = true;
        for(int i = head[u] ; i ; i = E[i].u) {
            int v = E[i].v;
            if(dis[u] + E[i].h < dis[v])
                q.emplace(dis[v] = dis[u] + E[i].h,v);
        }
    }
}

struct Compare {
    inline bool operator ()(const edge &a,const edge &b) 
    { return a.h > b.h; }
};

void kruskal() { /* Kruskal tree */
    memset(head,0,sizeof(head)); tot = 0;
    dark::heap <edge,Compare> hp;
    for(int i = 1 ; i <= m ; ++i) hp.push(e[i]);
    for(int i = 1 ; i <= m ; ++i) {
        e[i] = hp.top();
        hp.pop();
    }
    for(int i = 1 ; i <= n ; ++i) anc[i] = i;
    for(int i = 1 ; i <= m ; ++i)  {
        int x = find(e[i].u);
        int y = find(e[i].v);
        if(x == y) continue; 
        h[++cnt] = e[i].h;
        anc[x] = anc[y] = anc[cnt] = cnt;
        adde(cnt,x,0) , adde(cnt,y,0);
    }
}

void dfs(int u)  {
    minn[u] = dis[u];
    for(int i = head[u] ; i ; i = E[i].u) {
        int v = E[i].v;
        fat[0][v] = u;
        dfs(v);
        minn[u] = min(minn[u],minn[v]);
    }
}

int logn = 0;
void prework() {
    memset(minn,120,sizeof(minn));
    dark::read(n,m);
    cnt = n;
    for(int i = 1; i <= m ; ++i) {
        int u,v,d,h;
        dark::read(u,v,d,h);
        adde(u,v,d) , adde(v,u,d);
        e[i] = {u,v,h};
    }
    dijkstra(); kruskal(); dfs(cnt);
    for(int i = 1 ; (1 << (logn = i)) <= cnt ; ++i)
        for(int u = 1 ; u <= cnt ; ++u)
            fat[i][u] = fat[i - 1][fat[i - 1][u]];
}

int main()  {
    int T = dark::read(T);
    while(T--) {
        prework();
        dark::read(Q,K,S);
        int lastans = 0;
        while(Q--) {
            int v,p;
            dark::read(v,p);
            v = (v + K * lastans - 1) % n + 1;
            p = (p + K * lastans) % (S + 1);
            for(int j = logn ; j >= 0 ; --j)
                if(h[fat[j][v]] > p) 
                    v = fat[j][v];
            dark::writeline(lastans = minn[v]);
        }
        if(T) {
            tot = 0;
            memset(head,0,sizeof(head));
        }
    }
    return 0;
}
