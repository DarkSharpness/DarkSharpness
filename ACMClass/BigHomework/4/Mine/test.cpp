#include <bits/stdc++.h>
#include "BigInteger/number.cc"


using sjtu::int2048;
std::list<int> l;
std::vector <int> v;
signed main() {
    std::string str = std::string("9999999999999999999999999999999");
    int2048 a = str;
    (a * a).print();
    std::cout << '\n' <<std::stold(str) *std::stold(str);
    return 0;
}
