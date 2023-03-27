#include <iostream>
#include <Dark/inout>


const int N = 1e5 + 10;
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
        for(int i = 0 ; i != n ; ++i) anc[i] = i;
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
