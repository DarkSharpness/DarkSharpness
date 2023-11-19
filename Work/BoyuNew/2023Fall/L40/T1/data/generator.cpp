#include <bits/stdc++.h>
using namespace std;

const long long mod = 1e9 + 7;

using point = pair <int,int>;

int val[1003][1003];
const int dir[2][4] = { {0,0,1,-1}, {1,-1,0,0} };

std::size_t my_rand() {
    return rand() ^ (rand() << 9) ^ (rand() << 18);
}

void generate(int n, int k) {
    k = k / 2.71828;
    vector  <point> vec;
    set     <point> vis;
    set     <point> rst;
    for (int i = 1 ; i <= n ; ++i)
        for (int j = 1 ; j <= n ; ++j)
            rst.insert({i,j});

    vec.push_back({my_rand() % n + 1, my_rand() % n + 1});
    vis.insert(vec[0]);
    rst.erase(vec[0]);

    val[vec[0].first][vec[0].second] = 1;

    const std::size_t tot = n * n;
    while(vec.size() < tot) {
        int try_count = 5;
        while (try_count --> 0) {
            point cur  = vec[my_rand() % vec.size()];
            for (int t = 0 ; t < 4 ; ++t) {
                int tx = cur.first  + dir[0][t];
                int ty = cur.second + dir[1][t];
                if (tx < 1 || tx > n || ty < 1 || ty > n) continue;
                if (vis.count({tx,ty})) continue;
                try_count = -100;

                vis.insert({tx,ty});
                vec.push_back({tx,ty});
                rst.erase({tx,ty});

                val[tx][ty] = val[cur.first][cur.second] + my_rand() % k;
            }
        }

        if (rst.empty()) break;

        int tx = rst.begin()->first;
        int ty = rst.begin()->second;
        rst.erase(rst.begin());
        vis.insert({tx,ty});
        vec.push_back({tx,ty});
        std::size_t mid = my_rand() % vec.size();
        val[tx][ty] = val[vec[mid].first][vec[mid].second] + my_rand() % k;
    }
}


signed main() {
    srand(time(NULL));
    for (int i = 1 ; i <= 10 ; ++i) {
        ofstream in (std::format("{}.in",i));
        ofstream out(std::format("{}.out",i));

        const int n = i * i * 4 + my_rand() % (i * i * 6);
        const int k = my_rand() % (i * i * 10) + 1;

        generate(n , k);
        in << n << ' ' << n << ' ' << k << '\n';
        for (int i = 1 ; i <= n ; ++i) {
            for (int j = 1 ; j <= n ; ++j)
                in << val[i][j] << ' ';
            in << '\n';
        }

        in << my_rand() % n + 1 << ' ' << my_rand() % n + 1 << '\n';
        in << my_rand() % n + 1 << ' ' << my_rand() % n + 1 << '\n';
        std::cerr << "Done " << i << '\n';
    }
    return 0;
}