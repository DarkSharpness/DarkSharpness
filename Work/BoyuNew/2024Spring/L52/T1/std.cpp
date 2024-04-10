#include <iostream>
#include <vector>
using namespace std;
const int N = 1e5 + 3;
vector <int> g[N];
bool vis[N];
bool found;

void dfs(int x, int from) {
    if (vis[x]) { found = true; return; }
    vis[x] = true;
    for (auto v : g[x])
        if (v != from) dfs(v, x);
}


int main()  {
    int n, m;
    cin >> n >> m;
    for (int i = 1 ; i <= m ; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for (int i = 1 ; i <= n ; ++i)
        if (!vis[i]) dfs(i, 0);

    cout << (found ? "YES" : "NO"); 
}

