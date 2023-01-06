#include <bits/stdc++.h>
// #include <Dark/inout>
using namespace std;
using ll = long long;
using ull = unsigned long long;
// #define int long long

constexpr long double operator"" _multiply2(long double x) {
    return x * 2;
}

constexpr bool testDigit(char _ch) {
    return '0' <= _ch && _ch <= '9';
}

constexpr size_t operator"" _toint(const char *str,size_t y) {
    size_t ans = 0;
    for(size_t i = 0 ; i < y ; ++i) {
        if(testDigit(str[i]))
            ans = ans * 10 + (str[i] ^ '0');
    }
    return ans;
}

constexpr size_t operator"" _multiply3(size_t x) {
    return x * 3;
}

struct number : std::vector <int> {
    constexpr number(const char *__str) {
        while(*__str) {
            this->push_back(*(__str++) ^ '0');
        }
    }
};

using namespace std::string_literals;

constexpr double tmp = 3.14_multiply2;
constexpr size_t len = 114514123123333333333333131231222222222_multiply3;
constexpr size_t num = "123456dada7"_toint;
// constexpr number con("123"); // this is wrong

signed main() {
    // char string that use original format
    const char *str = R"begin(Hastin
is a good man.
I \n love him!
)begin"; // The string before ( and after ) should be identical.
    std::cout << str;
    std::cout << tmp << '\n'
              << len << '\n'
              << num << '\n';
    auto s = "This is a std::string style string"s;
    return 0;
}