#include <iostream>
using namespace std;

const int N = 501;
bool g[N][N];

signed main() {
    int m,q;
    cin >> m >> q;
    while(m--) {
        int x,y;
        cin >> x >> y;
        g[y][x] = g[x][y] = true;
    }
    while(q--) {
        int x,y;
        cin >> x >> y;
        if(g[x][y]) cout << "Yes\n";
        else        cout << "No\n";
    }
    return 0;
}