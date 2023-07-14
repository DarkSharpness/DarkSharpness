#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

const int N = 5e4 + 3;
int f[N];
int anc[N]; /* Ancestor. */
struct node {
    union {
        struct {
            int ls,rs;
        };
        int son[2];
    };
} t[N];

int get(int x) {
    return anc[x] ? anc[x] = get(anc[x]) : x;
}

bool check(int x,int y) {
    return get(x) == get(y);
}

void generate_tree(vector <int> &v) {
    int n = v.size() + 1;
    for(int i = 1 ; i <= n ; ++i) {
        int cnt = 0;
        // Try to generate son for 8 times.
        for(int j = 0 ; j < 4 ; ++j) {
            if(!v.size()) break;
            auto iter = v.begin() + (rand() % v.size());
            if(check(*iter,i) || rand() & 0b10) continue;
            anc[t[i].son[cnt] = *iter] = i;
            swap(*iter,v.back());
            v.pop_back();
            if(++cnt == 2) break;
        }
        while(cnt != 2) t[i].son[cnt++] = 0;
    }
    if(v.size() != 0) throw;
}

int dfs(int x) {
    if(!x) return 0;
    f[x] = 1;
    f[x] += dfs(t[x].ls);
    f[x] += dfs(t[x].rs);
    return f[x];
}

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 8 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        const int n = 10 * i * i * i;
        memset(anc,0,sizeof(int) * (n + 1));
        memset( f ,0,sizeof(int) * (n + 1));
        vector <int> v(n - 1);
        iota(v.begin(),v.end(),2);
        generate_tree(v);
        for(int i = 1 ; i <= n ; ++i)
            if(!f[i]) dfs(i);
        freopen(in.data(),"w",stdout);
        dark::writeline(n);
        for(int i = 1 ; i <= n ; ++i){
            if(rand() & 1) swap(t[i].ls,t[i].rs);
            dark::writeline(t[i].ls,t[i].rs);
        }
        freopen(out.data(),"w",stdout);
        for(int i = 1 ; i <= n ; ++i)
            dark::writeline(f[i]);
    }
    return 0;
}