#include <bits/stdc++.h>
#include "BigInteger/number.cc"


using sjtu::int2048;
std::list<int> l;
std::vector <int> v;
signed main() {
    int2048 a,b;
    while(std::cin >> a >> b)
        std::cout << bool(a * b) << '\n';
    return 0;
}
