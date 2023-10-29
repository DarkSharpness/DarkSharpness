#include <iostream>
using namespace std;

int ans = 0;
int n;

int b[15];

void dfs(int x,int y) {
    if (x > n) { ++ans; return; }
    for(int i = 1; i < y - 1; ++i) {
        if (!b[i]) {
            b[i] = 1;
            dfs(x + 1,i);
            b[i] = 0;
        }
    }
    for(int i = y + 2; i <= n; ++i) {
        if (!b[i]) {
            b[i] = 1;
            dfs(x + 1,i);
            b[i] = 0;
        }
    }
}

int main() {
    cin >> n;
    dfs(1, -1);
    cout << ans;
    return 0;
}