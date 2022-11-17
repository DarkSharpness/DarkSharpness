#include <bits/stdc++.h>
#include "BigInteger/number.cc"


using sjtu::int2048;
std::list<int> l;
std::vector <int> v;
signed main() {
    std::string str = std::string("1000000000000000001");
    int2048 a = str;
    a = (a * a) * (a * a);
    try {
        (a * -a).print();
    }catch(const char * s) {
        std::cout << s;
    }
    // std::cout << '\n' <<std::stold(str) *std::stold(str);
    return 0;
}
