#include <iostream>
using namespace std;

signed main() {
    long long n; // 可以用 unsigned 代替,总之小心越界
    cin >> n;
    long long y = n;
    long long a = 0;
    long long b = 0;

    // 可以证明,最大的完美数不会超过 9999
    if(y < 10000) { // 最多有四位
        a += (y % 10) * (y % 10) * (y % 10);
        b += (y % 10) * (y % 10) * (y % 10) * (y % 10);
        y /= 10;
        a += (y % 10) * (y % 10) * (y % 10);
        b += (y % 10) * (y % 10) * (y % 10) * (y % 10);
        y /= 10;
        a += (y % 10) * (y % 10) * (y % 10);
        b += (y % 10) * (y % 10) * (y % 10) * (y % 10);
        y /= 10;
        a += (y % 10) * (y % 10) * (y % 10);
        b += (y % 10) * (y % 10) * (y % 10) * (y % 10);
        y /= 10;
    }

    if(a == n || b == n) {
        cout << n << " is a perfect number";
    } else {
        cout << n << " is not a perfect number";
    }

    return 0;
}
