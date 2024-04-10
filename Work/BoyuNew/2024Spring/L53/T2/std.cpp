#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1e4 + 3;
struct Edge {
    int u, v, w;
} edge[N];
int anc[N]; // Parent of each node

bool cmp(Edge a, Edge b) { return a.w < b.w; }

int find_root(int u) {
    if (anc[u] == u) return u;
    return anc[u] = find_root(anc[u]);
}


signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) anc[i] = i;
    for (int i = 1; i <= m; i++)
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
    sort(edge + 1, edge + m + 1, cmp);
    int cnt = 1;
    int res = 0;
    for (int i = 1; i <= m; i++) {
        int u = edge[i].u, v = edge[i].v, w = edge[i].w;
        int root_u = find_root(u), root_v = find_root(v);
        if (root_u != root_v) {
            anc[root_u] = root_v;
            res += w;
            if (++cnt == n) break;
        }
    }
    cout << res << '\n';
    return 0;
}
