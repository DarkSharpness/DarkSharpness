#include <bits/stdc++.h>
#include <Dark/inout>

using namespace std;

const int N = 1e6 + 10;
int anc[N];

struct edge {
    int x,y,w;
    int color;
} b[N],w[N];
int topb = 0,topw = 0;

inline bool cmp(const edge &l,const edge &r) 
noexcept { return l.w < r.w; }

int find(int x) noexcept
{ return anc[x] == x ? x : (anc[x] = find(anc[x])); }


signed main() {
    int n,m,k;
    dark::read_u(n,m,k);

    for(int i = 0 ; i < m ; ++i) {
        int x,y,t;
        dark::read_u(x,y,t);
        char ch = dark::read_char(ch);
        (ch == '0' ? w[topw++] : b[topb++]) = (edge) {y,x,t,ch};
    }

    std::sort(b , b + topb , cmp);
    b[topb].w = 114514;
    std::sort(w , w + topw , cmp);
    w[topw].w = 1919810;

    int l = -103 , r = 103;
    int mid = 0;
    int ans = 191981000;

    while(l != r) { // At most limited times
        mid = (l + r) >> 1;
        std::iota(anc , anc + n , 0);
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
            wcnt += (ptr->color == '0'); 
            anc[x] = y;
            ++cnt;
        }
        if(wcnt >= k) { l = mid + 1; ans = sum + (wcnt - k) * mid; }
        else r = mid;
    }
    printf("%d",ans);
    return 0;
}
