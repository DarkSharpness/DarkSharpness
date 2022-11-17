/*
Time: 2021-10-21
Test: mul
std Time: 0.01s
Time Limit: 1.00s
*/

#include "int2048.hpp"

sjtu::int2048 a, b;

int main()
{
    freopen("8.in","r",stdin);
    freopen("ans.out","w",stdout);
    int T;
    std::cin >> T;
    while (T--)
    {
        std::cin >> a >> b;
        std::cout << a * b << '\n';
        std::cout << (a *= b) << '\n';
        a *= b;
        a *= a;
        a *= b;
        std::cout << (b *= a) << '\n';
    }
}