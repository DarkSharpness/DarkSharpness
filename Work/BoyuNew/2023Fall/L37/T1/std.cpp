#include <iostream>
using namespace std;


int a[13];
int b[13];
int n;

void dfs(int x) {
    if (x == n + 1) {
        for (int i = 1; i <= n; i++) cout << a[i] << ' ';
        cout << '\n';
        return;
    }
    for(int i = 1 ; i <= n ; ++i) {
        if (!b[i]) {
            b[i] = 1;
            a[x] = i;
            dfs(x + 1);
            b[i] = 0;
        }
    }
}


signed main() {
    cin >> n;
    dfs(1);
    return 0;
}