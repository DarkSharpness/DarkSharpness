#include <iostream>
#include <vector>
using namespace std;

const int N = 1e4 + 2;
vector<int> g[N];
bool vis[N];
bool has_cycle = false;

/// u: current node, p: parent node
void dfs(int u, int p) {
    vis[u] = true;
    for (int v : g[u]) {
        // Don't go back to parent
        if (v == p) continue;
        if (!vis[v]) dfs(v, u);
        else has_cycle = true;
    }
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0 ; i < m ; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int cnt = 0;
    for (int i = 1 ; i <= n ; ++i)
        if (!vis[i]) { dfs(i, 0); ++cnt; }
    if (has_cycle) cnt = 0;
    cout << cnt << endl;
    return 0;
}