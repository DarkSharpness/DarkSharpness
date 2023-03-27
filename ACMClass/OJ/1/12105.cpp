#include <iostream>
#include <Dark/inout>


const int N = 1e5 + 7;
struct pair { int id,h; };
pair st[N];
int top = 0;

inline void update(long long &x,long long y) { if(x < y) x = y; }

signed main() {
    int n = dark::read_u(n);
    long long ans = st[0].h = 0;
    for(int i = 0 ; i < n ; ++i) {
        int h = dark::read_u(h);
        if(h == st[top].h) continue;
        int l = i;
        while(h < st[top].h) {
            update( ans , st[top].h * (long long)(i - (l = st[top].id)) );
            --top;
        }
        st[++top].id = l;
        st[top].h = h;
    }
    while(top) {
        update(ans,st[top].h * (long long)(n - st[top].id) );
        --top;
    }
    printf("%lld",ans);
    return 0;
}
