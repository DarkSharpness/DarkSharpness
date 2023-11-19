#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int N = 1003;
int a[N][N];
bool vis[N][N];

struct point { int x,y; int step; };

const int dir[2][4] = { {0,0,1,-1}, {1,-1,0,0} };

signed main() {
    int n,m,k;
    cin >> n >> m >> k;
    for(int i = 1 ; i <= n ; ++i)
        for(int j = 1 ; j <= m ; ++j)
            cin >> a[i][j];

    std::queue <point> q;
    point tmp;
    cin >> tmp.x >> tmp.y;
    tmp.step = 0;
    q.push(tmp);
    cin >> tmp.x >> tmp.y;

    while(!q.empty()) {
        point cur = q.front(); q.pop();
        if (cur.x == tmp.x && cur.y == tmp.y) {
            cout << cur.step << '\n';
            return 0;
        }
        vis[cur.x][cur.y] = true;
        for (int t = 0 ; t < 4 ; ++t) {
            int tx = cur.x + dir[0][t];
            int ty = cur.y + dir[1][t];
            if (tx < 1 || tx > n || ty < 1 || ty > m) continue;
            if (vis[tx][ty]) continue;
            if (std::abs(a[tx][ty] - a[cur.x][cur.y]) > k) continue;
            vis[tx][ty] = true;
            q.push( { tx , ty , cur.step + 1});
        }
    }

    cout << -1 << '\n';
    return 0;
}