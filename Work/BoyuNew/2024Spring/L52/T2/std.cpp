#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int N     = 1e5 + 3;
const int INF   = 1e9 + 7;
int dis[N];
vector <int> g[N];


signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1 ; i <= m ; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    for (int i = 1 ; i <= n ; ++i) dis[i] = INF;

    int s;
    cin >> s;

    dis[s] = 0;
    std::queue <int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) {
            // Not visited case.
            if (dis[v] == INF) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }

    for (int i = 1 ; i <= n ; ++i) {
        if (dis[i] == INF)  cout << "-1 ";
        else                cout << dis[i] << ' ';
    }

    return 0;
}
