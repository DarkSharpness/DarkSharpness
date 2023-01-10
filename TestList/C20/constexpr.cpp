#include <bits/stdc++.h>
#include <numeric>

/* C++ 20 feature: Dynamic allocation. */
class string {
  public:
    char *ptr;
    size_t len;
    constexpr string(const char *str) {
        len = strlen(str);
        ptr = new char[len + 1];
        for(size_t i = 0 ; i != len ; ++i) ptr[i] = str[i];
        ptr[len] = 0;
    }
    constexpr char &operator[](size_t __n) {
        return ptr[__n];
    }
    constexpr char operator [](size_t __n) const {
        return ptr[__n];
    }
    constexpr ~string() { /* Constexpr memory should be freed at constexpr time */
        delete []ptr;
    }
};
constexpr char ch = string("abcdef")[0];

// constexpr  // This is illegal
string str("abc"); // No constexpr ! 
// Because constexpr memory should be retrieved in constexpr time.

signed main() {
    str[0] = 'a';

    return 0;
}