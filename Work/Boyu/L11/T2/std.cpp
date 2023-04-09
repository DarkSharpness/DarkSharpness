#include <iostream>
using namespace std;

const int N = 101;
int s[N][N]; // 不要抄答案! 这是前缀和写法!


signed main() {
    int n,m;
    cin >> n >> m;
    for(int i = 1 ; i <= n ; ++i)
        for(int j = 1 ; j <= m ; ++j) {
            cin >> s[i][j];
            s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
        }
    int a,b,c,d;
    cin >> a >> b >> c >> d;
    cout << s[c][d] - s[a - 1][b - 1];
    return 0;
}