#include <iostream>
#include <queue>
using namespace std;


const int N = 1e3 + 3;
char mp[N][N];
struct point {
    int x, y;
    int step;
};

const int tx[] = {0, 0, 1, -1};
const int ty[] = {1, -1, 0, 0};

queue <point> q;

signed main() {
    int n,m;
    cin >> n >> m;
    for(int i = 1 ; i <= n ; ++i)
        for(int j = 1 ; j <= m ; ++j) {
            cin >> mp[i][j];
            if (mp[i][j] == 'S') {
                mp[i][j] = '#'; // 防止走重复的点
                point start;
                start.x = i, start.y = j;
                start.step = 0;
                q.push(start);
            }
        }

    while(!q.empty()) {
        point now = q.front(); q.pop();
        int x = now.x, y = now.y;
        for(int t = 0 ; t < 4 ; ++t) {
            int xx = x + tx[t], yy = y + ty[t];
            // 找到了终点
            if (mp[xx][yy] == 'E') {
                cout << now.step + 1;
                return 0;
            }

            // 在边界外的点，或者是墙，或者已经来过
            if (mp[xx][yy] != '.') continue;

            mp[xx][yy] = '#'; // 防止走重复的点

            point next;
            next.x = xx, next.y = yy;
            next.step = now.step + 1;
            q.push(next);
        }
    }

    cout << 0;

    return 0;
}
