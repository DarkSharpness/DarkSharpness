#include <iostream>
#include <algorithm>
using namespace std;

int a[100][100]; // 原数组
int s[100][100]; // 前缀和数组

int main() {
    int n,m;
    cin >> n >> m;
    for(int i = 1 ; i <= n ; ++i)
        for(int j = 1 ; j <= m ; ++j) {
            cin >> a[i][j];
            s[i][j] = a[i][j] + s[i][j - 1]
                    + s[i - 1][j] - s[i - 1][j - 1];
        }
    int ans = 0;
    for(int i = 2 ; i <= n ; ++i)
        for(int j = 2 ; j <= m ; ++j)
            if(s[i][j] - s[i - 2][j]
             - s[i][j - 2]+ s[i - 2][j - 2] == 0)
                ++ans;
    cout << ans << '\n';
    return 0;
}