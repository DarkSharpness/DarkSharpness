#include <array>
#include <iostream>

const int N = 1003;

using _Data_Type = std::array <long long,N>;

constexpr _Data_Type table() {
    _Data_Type x = {0,1};
    for(int i = 2 ; i < N ; ++i)
        x[i] = x[i >> 1] + x[i - 1] + 1;
    return x;
}

constexpr auto dp = table();

signed main() {
    int n;
    std::cin >> n;
    std::cout << dp[n >> 1] + 1;
    return 0;
}
