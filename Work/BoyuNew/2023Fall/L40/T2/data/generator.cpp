#include <bits/stdc++.h>
using namespace std;

bool t[4][4];

int make(int n) {
    int ans = 0;
    for (int i = 0 ; i < n ; ++i)
        for (int j = 0 ; j < n ; ++j)
            ans |= t[i][j] << (i * n + j);
    return ans;
}

void split(int val,int n) {
    for (int i = 0 ; i < n ; ++i)
        for (int j = 0 ; j < n ; ++j)
            t[i][j] = (val >> (i * n + j)) & 1;
}

const int N = 1 << 16;
bool vis[N];
struct point { int state, step; };
vector <int> feasible;

void std_program(int n) {
    static int last = 0;
    if (last == n) return;
    last = n;

    memset(vis , 0 , sizeof (vis));
    queue <point> q;
    q.push({0 , 0});

    int mask1 = (1 << n) - 1;   // 交换一行
    int mask2 = 0;              // 交换一列
    for (int i = 0 ; i < n ; ++i) mask2 |= 1 << (i * n);

    while (!q.empty()) {
        const int val = q.front().state;
        const int step = q.front().step + 1;
        q.pop();
        vis[val] = true;
        for (int i = 0 ; i < n ; ++i) {
            int nxt = val ^ (mask1 << (i * n));
            if (vis[nxt]) continue;
            vis[nxt] = true;
            q.push({ nxt, step });
        }

        for (int i = 0 ; i < n ; ++i) {
            int nxt = val ^ (mask2 << i);
            if (vis[nxt]) continue;
            vis[nxt] = true;
            q.push({ nxt, step });
        }
    }

    for (int i = 0 ; i < (1 << n * n) ; ++i)
        if (vis[i]) feasible.push_back(i);
    return;
}


signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        ofstream in (std::format("{}.in",i));
        ofstream out(std::format("{}.out",i));
        const int n = (i + 9) / 4;
        std_program(n);

        in << n << endl;

        std::random_shuffle(feasible.begin() , feasible.end());
        split(feasible[0] , n);

        for (int i = 0 ; i < n ; ++i)
            for (int j = 0 ; j < n ; ++j)
                in << t[i][j] << " \n"[j == n - 1];

    }
    return 0;
}
