#include <iostream>
#include <algorithm>

const int N = 103;

std::string str[N];

signed main() {
    int n;
    std::cin >> n;
    for(int i = 0 ; i < n ; ++i)
        std::cin >> str[i];
    std::sort(str,str + n);
    for(int i = n - 2 ; i >= 0 ; --i)
        str[n - 1] += str[i];
    std::cout << str[n - 1];
    return 0;
}
