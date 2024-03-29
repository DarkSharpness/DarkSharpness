#include <iostream>
#include <vector>
using namespace std;

const int N = 1e6 + 3;

vector <int> son[N];
int siz[N];


int dfs(int x) {
    if (siz[x]) return siz[x];
    siz[x] = 1;
    for (auto y : son[x])
        siz[x] += dfs(y);
    return siz[x];
}

signed main() {
    int n;
    cin >> n;
    for (int i = 1 ; i <= n ; ++i) {
        int x;
        cin >> x;
        son[x].push_back(i);
    }
    for (int i = 1 ; i <= n ; ++i)
        std::cout << dfs(i) << ' ';
    return 0;
}
