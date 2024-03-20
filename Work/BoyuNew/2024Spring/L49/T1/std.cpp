#include <iostream>

const int N = 5005;
int nxt[N];

int get_circle_length(int x) {
    int y = x;
    int cnt = 0;
    do {
        x = nxt[x];
        y = nxt[nxt[y]];
        cnt++;
    } while (x != y);
    return cnt;
}

int try_find_circle(int x) {
    int y = x;
    do {
        x = nxt[x];
        y = nxt[nxt[y]];
    } while (x != y);
    if (x == 0) return 0; // No circle case
    return get_circle_length(x);
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
