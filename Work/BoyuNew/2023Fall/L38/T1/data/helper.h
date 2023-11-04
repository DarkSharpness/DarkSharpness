#include <bits/stdc++.h>

const int N = 1009;
char mp[N][N];


struct point {
    int x, y;
    friend bool operator == (point,point) = default;
};


struct edge {
    point a,b;
    friend bool operator == (edge x,edge y) {
        return (x.a == y.a && x.b == y.b)
            || (x.a == y.b && x.b == y.a);
    }
};

struct point_hash {
    std::size_t operator()(point p) const noexcept {
        using ll = std::size_t;
        return ll(p.x) | (ll(p.y) << 10);
    }
};

struct edge_hash {
    std::size_t operator()(edge e) const noexcept {
        return point_hash()(e.a) | point_hash()(e.b) << 20;
    }
};

void make_map(int len) {
    std::unordered_set <point,point_hash> visit;
    std::unordered_set <edge, edge_hash> link;
    std::queue <point> q;

    static point __arr[] = {point{0,1},point{0,-1},point{1,0},point{-1,0}};

    auto &&dfs = [&](auto &&self, point p) -> void {
        if (!visit.insert(p).second) return; // visited!
        std::swap(__arr[rand() & 3], __arr[rand() & 3]);

        for (auto [dx,dy] : __arr) {
            int xx = p.x + dx, yy = p.y + dy;
            if (rand() % 3 == 0) continue;
            if (xx < 1 || yy < 1 || xx > len || yy > len) continue;
            if (visit.count({xx,yy})) continue;
            if (link.insert(edge{{p.x,p.y},{xx,yy}}).second)
                self(self, {xx,yy});
        }
    };

    dfs(dfs, {rand() % len + 1 ,rand() % len + 1});

    std::memset(mp,'#',sizeof(mp));

    for(int i = 1 ; i <= len ; ++i)
        for(int j = 1 ; j <= len ; ++j)
            mp[i * 2 - 1][j * 2 - 1] = '.';

    for(int i = 1 ; i <= len ; ++i)
        for(int j = 1 ; j <= len ; ++j) {
            for(auto [dx,dy] : __arr) {
                int xx = i + dx, yy = j + dy;
                if (link.count(edge{{i,j},{xx,yy}})) {
                    mp[i * 2 - 1 + dx][j * 2 - 1 + dy] = '.';
                }
            }
        }
}

void print_map(int len) {
    std::vector <point> vec;
    for(int i = 1 ; i <= len ; ++i)
        for(int j = 1 ; j <= len ; ++j)
            if (mp[i][j] == '.') vec.push_back({i,j});
    
    if (vec.size() < 2) throw;
    std::random_shuffle(vec.begin(),vec.end());

    mp[vec[0].x][vec[0].y] = 'S';
    mp[vec[1].x][vec[1].y] = 'E';

    for(int i = 1 ; i <= len ; ++i)
        for(int j = 1 ; j <= len ; ++j)
            std::cout << mp[i][j] << " \n"[j == len];
}

// signed main() {
//     int n;
//     std::cin >> n;
//     make_map(n);
//     for(int i = 1 ; i <= 2 * n - 1 ; ++i)
//         for(int j = 1 ; j <= 2 * n - 1 ; ++j)
//             std::cout << mp[i][j] << " \n"[j == 2 * n - 1];
//     return 0;
// }