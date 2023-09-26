#include <bits/stdc++.h>
using namespace std;

char mp[102][102];
int dir[4][2] = {
    {0,1},
    {0,-1},
    {1,0},
    {-1,0}
};

signed main() {
    int n,m;
    cin >> n >> m;
    for(int i = 1 ; i <= n ; ++i)
        scanf("%s",mp[i] + 1);
    bool tag = false;
    do {
        tag = false;
        for(int i = 1 ; i <= n ; ++i)
            for(int j = 1 ; j <= m ; ++j) {
                if(mp[i][j] != '*') continue;
                int cnt = 0;
                for(int k = 0 ; k < 4 ; ++k) {
                    int x = i + dir[k][0];
                    int y = j + dir[k][1];
                    if(mp[x][y] == '-') ++cnt;
                }
                if(cnt >= 2) {
                    tag = true;
                    mp[i][j] = '-';
                }
            }
    } while(tag);
    for(int i = 1 ; i <= n ; ++i)
       puts(mp[i] + 1);
    return 0;
}