#include <iostream>
using namespace std;


signed main() {
    int n,m;
    cin >> n >> m;
    for(int i = 0 ; i < n ; ++i) {
        for(int j = 0 ; j < m ; ++j)
            cout << "*"; // 如果学过字符，可以用 '*' 代替
        cout << '\n'; 
        // 请不要用 endl 表示换行，其效率略低于 \n
    }
    return 0;
}