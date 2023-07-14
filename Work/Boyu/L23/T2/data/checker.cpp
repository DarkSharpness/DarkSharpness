#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 2;
bool f[N]; // 大小
struct node {
    int ls,rs;
}t[N];

void dfs(int x) {
    if(!x) return;
    if(f[x]) throw;
    f[x] = 1;
    dfs(t[x].ls);
    dfs(t[x].rs);
}

signed main() {
    int n;
    for(int i = 1 ; i <= 8 ; ++i) {
        string in  = to_string(i) + ".in";
        freopen(in.c_str(),"r",stdin);
        std::cin >> n;
        memset(f,0,sizeof(int) * (n + 1));
        for(int i = 1 ; i <= n ; ++i)
            std::cin >> t[i].ls >> t[i].rs;
        for(int i = 1 ; i <= n ; ++i)
            if(!f[i]) dfs(i);
    } std::cout << "Pass\n";
    return 0;
}