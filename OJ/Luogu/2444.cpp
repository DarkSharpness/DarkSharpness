#include <bits/stdc++.h>
// #include <Dark/inout>

const int N = 3e4 + 5;
struct node {
    int  fail;
    bool safe;
    int  id[2];
    node() noexcept : fail(0),safe(0),id{0,0} {}
}t[N];

std::bitset <N> vis,st;

inline bool &safe(int x) { return t[x].safe; }
inline int  &fail(int x) { return t[x].fail; }
inline int  *id(int x)   { return t[x].id;   }

int qq[N],hd,tl;
struct queue {
    void push(int x) noexcept { qq[++tl] = x; }
    int pop() noexcept { return qq[++hd]; }
    bool size() noexcept { return hd != tl; }
};


inline bool is(char c) { return c == '0' || c == '1'; }

void dfs(int u) {
    if(st[u]) { puts("TAK"); exit(0); }
    if(vis[u] || safe(u)) return;
    st[u] = vis[u] = true;
    dfs(id(u)[0]);
    dfs(id(u)[1]);
    st[u] = false;
}

struct darksharpness {
    int cnt;
    void insert() noexcept {
        char ch;
        int x = 0;
        while(!is(ch = getchar()));
        while(is(ch)) {
            int &t = id(x)[ch == '1'];
            x = (t ? t : t = ++cnt);
            ch = getchar();
        }
        safe(x) = true;
    }

    void build() {
        queue q;

        if(id(0)[0]) q.push(id(0)[0]);
        if(id(0)[1]) q.push(id(0)[1]);

        while(q.size()) {
            int x = q.pop();
            for(int i = 0,v ; i < 2 ; ++i) {
                if((v = id(x)[i])) {
                    fail(v) = id(fail(x))[i];
                    safe(v) |= safe(fail(v));
                    q.push(v);
                } else {
                    id(x)[i] = id(fail(x))[i];
                }
            }
        }
    }

    darksharpness() noexcept : cnt(0) {}

} hastin;

signed main() {
    int n;
    scanf("%d",&n);
    for(int i = 0 ; i < n ; ++i) hastin.insert();
    hastin.build();
    dfs(0);
    puts("NIE");
    return 0;
}