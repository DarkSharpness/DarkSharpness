#include <bits/stdc++.h>
#include "BigInteger/number.cc"


using sjtu::int2048;
std::list<int> l;
std::vector <int> v;
signed main() {
    std::string str = std::string("1000000000010000000000100000000001");
    int2048 a = str;
    (a * a * a).print();
    return 0;
}
