#include <bits/stdc++.h>
#include <Dark/inout>

const int N = 1003;
int n,m;

char g[N][N];
int  v[N][N][2];

struct node {
    int x,y;
    bool state;
    node() = default;
    node(int a,int b,bool c) { x = a , y = b, state = c; }
};

std::queue <node> q;

const int dir[2][4] = {
    { 1,0,-1,0 },
    { 0,1,0,-1 }
};

bool check(int x,int y,bool z) {
    if(x < 0 || y < 0 || x >= n || y >= m) return false;
    if(v[x][y][z] || g[x][y] == '1') return false;
    return true;
}


void bfs() {
    while(!q.empty()) {
        auto [x,y,z] = q.front();
        q.pop();
        for(int i = 0 ; i < 4 ; ++i) {
            int tx = x + dir[0][i];
            int ty = y + dir[1][i];
            if(!check(tx,ty,z)) continue;

            v[tx][ty][z] = v[x][y][z] + 1;
            q.emplace(tx,ty,z);

            if(z && g[tx][ty] == '3') {
                // printf("%d %d\n",tx,ty);
                printf("%d",v[tx][ty][z]);
                break;
            }

            if(!z && g[tx][ty] == '4' && !v[tx][ty][1]) {
                v[tx][ty][1] = v[x][y][0] + 1;
                q.emplace(tx,ty,1);
            }
        }
    }
}

signed main() {
    dark::read_u(m,n);
    for(int i = 0 ; i < n ; ++i)
        for(int j = 0 ; j < m ; ++j) 
            if(dark::read_char(g[i][j]) == '2')
                q.emplace(i,j,0);
    bfs();
    return 0;
}