#include <iostream>
using namespace std;

const int N = 1e5 + 3;
int a[N];
int b[N];

signed main() {
    int n, m = 0, p = 0;
    cin >> n;
    int x, y;
    while (n--) {
        cin >> x;
        if (x == 1) {
            cin >> y;
            a[++m] = y;
        } else if (x == 2) {
            y = b[++p] = a[m--];
            cout << y << '\n';
        } else if (x == 3) {
            a[++m] = b[p--];
        } else {
            for (int i = 1 ; i <= m ; ++i)
                cout << a[i] << ' ';
            cout << '\n';
        }
    }
    return 0;
}