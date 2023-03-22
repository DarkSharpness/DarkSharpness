#include <iostream>
using namespace std;


signed main() {
    int n;
    cin >> n;
    int m = n;
    int sum = 0;
    sum += (m % 10) * (m % 10) * (m % 10); // 个位
    m /= 10;
    sum += (m % 10) * (m % 10) * (m % 10); // 十位
    m /= 10;
    sum += (m % 10) * (m % 10) * (m % 10); // 百位
    if(sum == n) cout << "Yes";
    else cout << "No";
    return 0;
}
