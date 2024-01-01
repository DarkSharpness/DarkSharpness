#include <iostream>

const int N = 5000;
const int M = 1e9 + 7;
int a[N];
int b[N], c[N];

signed main() {
    int n;
    std::cin >> n;
    for (int i = 0 ; i < n ; ++i) std::cin >> a[i];

    for (int i = 1 ; i < n ; ++i)
        for (int j = 0 ; j != i ; ++j)
            if (a[j] < a[i]) b[i] = (b[i] + b[j] + 1) % M;

    for (int i = n - 2 ; i >= 0 ; --i)
        for (int j = n - 1 ; j != i ; --j)
            if (a[j] < a[i]) c[i] = (c[i] + c[j] + 1) % M;

    long long ans = 0;
    for (int i = 0 ; i < n ; ++i) ans += ((long long)(b[i]) * c[i]) % M;
    std::cout << ans % M << std::endl;
    return 0;
}
