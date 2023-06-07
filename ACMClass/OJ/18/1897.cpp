#include <iostream>
#include <cstring>

const int N = 152 * 502;
const int M = N;
const int V = 502;
struct query { int nxt,to,w,l; } e[V * V];
int head[V],tot = 0;
inline void adde(int fr,int to,int w,int l) noexcept
{ e[++tot] = {head[fr],to,w,l}; head[fr] = tot; }

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


double f[N]; 
int    p[N];
bool vis[N];
int    t[N];

void SPFA_is_dead() {
    Q.push(0 * V + 70);
    f[0 * V + 70] = 0;
    while(Q.size()) {
        int u = Q.pop();
        vis[u] = false;
        for(int i = head[u / V] ; i ; i = e[i].nxt) {
            int n = e[i].w ? e[i].w : u % V;
            double w = double(e[i].l) / n;
            int v = e[i].to * V + n;
            if(f[u] + w < f[v]) {
                f[v] = f[u] + w;
                p[v] = u;
                if(!vis[v]) vis[v] = true , Q.push(v);
            }
        }
    }
}


int st[V],top = 0;

signed main() {
    int n,m,d;
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m >> d;
    while(m--) {
        int a,b,v,l;
        std::cin >> a >> b >> v >> l;
        adde(a,b,v,l);
    }
    for(int i = 0 ; i < sizeof(f) / sizeof(double) ; ++i)
        f[i] = 1e12;
    SPFA_is_dead();
    double ans = 1e12;
    int    cur = 0;
    for(int i = 1 ; i < V ; ++i) {
        if(f[d * V + i] < ans) {
            cur = d * V + i;
            ans = f[cur];
        }
    }
    while(cur / V) {
        st[top++] = cur;
        cur = p[cur];
    }
    std::cout << "0 ";
    while(top--) std::cout << st[top] / V << ' ';
    return 0;
}
