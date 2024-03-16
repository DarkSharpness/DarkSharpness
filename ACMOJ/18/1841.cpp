#include <iostream>
#include <cmath>
#include <cstring>
#include <Dark/inout>

/* Read function part. */

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
