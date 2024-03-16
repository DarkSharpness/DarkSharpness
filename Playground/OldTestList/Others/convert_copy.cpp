#include <bits/stdc++.h>



signed main() {
    using A = const char *;
    using B = std::string;
    A x = "",y = "";
    B c,d;
    int result = 
    (x == y) + 
    (x == c) +
    (c == x) +
    (c == d);
    std::cout << result << '\n';
    // std::cout << (x == y) << '\n';
    return 0;
}
