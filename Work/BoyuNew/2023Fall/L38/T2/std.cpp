#include <bits/stdc++.h>
using namespace std;
const int N = 2003;
char mp[N][N];
const int dir[4][2] = {
    {0,1},
    {0,-1},
    {1,0},
    {-1,0}
};

struct point { int x,y; };
queue <point> q;

signed main() {
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i = 1 ; i <= n ; ++i) scanf("%s",mp[i] + 1);

    for(int i = 1 ; i <= n ; ++i)
        for(int j = 1 ; j <= m ; ++j)
            if (mp[i][j] == '*')
                q.push(point{i,j});

    while (!q.empty()) {
        point now = q.front(); q.pop();
        int x = now.x, y = now.y;

        // 边界外的点或者不是水源(已经被处理过)
        if (mp[x][y] != '*') continue;

        int cnt = 0;
        for(int t = 0 ; t < 4 ; ++t) {
            int tx = x + dir[t][0], ty = y + dir[t][1];
            if (mp[tx][ty] == '-') ++cnt; // 统计水源数量
        }

        // 水源数量不够
        if (cnt < 2) continue;
        mp[x][y] = '-'; // 水源数量够，处理该点

        // 寻找可能被更新的空气
        for(int t = 0 ; t < 4 ; ++t) {
            int tx = x + dir[t][0], ty = y + dir[t][1];
            if (mp[tx][ty] == '*') q.push(point{tx,ty});
        }
    }

    for(int i = 1 ; i <= n ; ++i) printf("%s\n",mp[i] + 1);
    return 0;
}