// #pragma GCC optimize(2)
#include "BigInteger/number.cc"

sjtu::int2048 a, b;
std::string s1, s2;

int main()
{
    freopen("ans.exe","w",stdout);
    for (int i = 1; i <= 10; i++)
    {
        a = 0, b = 0;
        s1 = "", s2 = "";
        for (int j = 1; j < 7000; j++)
            s1 += (1ll * (i + j) * 19260817) % 998244353 % 10 + '0';
        for (int j = 1; j < (i * 200); j++)
            s2 += (1ll * (i + j) * 998244353) % 19260817 % 10 + '0';
        a = s1; b = s2;
        b = b + 1; 
        if(i == 10) {
            std::cout <<'1';
        }
        std::cout << a / b << '\n';
    }
    return 0;
}