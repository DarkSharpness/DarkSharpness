#include <iostream>

const int N = 5005;
int nxt[N];
int cnt[N];

int try_find_circle(int x) {
    for (int i = 0 ; i < N ; ++i) cnt[i] = 0;
    int tot = 0;
    cnt[x] = ++tot;
    int y = nxt[x];
    while (y != 0) {
        // Visited before
        if (cnt[y] != 0) return cnt[x] - cnt[y] + 1;
        cnt[y] = ++tot;
        x = y;
        y = nxt[x];
    }
    return 0;
}


signed main() {
    int n, m;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
        std::cin >> nxt[i];
    std::cin >> m;
    while (m--) {
        int x;
        std::cin >> x;
        std::cout << try_find_circle(x) << '\n';
    }
    return 0;
}
