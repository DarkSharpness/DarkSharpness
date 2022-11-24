#include "vector.cc"

#include <Dark/inout>

using ll = long long;
using ull = unsigned long long;
//#define int lont long
using namespace sjtu;

signed main() {
    sjtu::array <int> a;
    a.reserve(6);
    a.resize(2);
    a.push_back(10);
    a.push_back(20);
    a.emplace_back(2);
    a.expand_front(3);
    // a.expand_front();
    a.expand_back(3);
    sjtu::array b = {1,3,4};
    b.swap(a);
    // a.~array();
    for(auto it : a) {
        dark::dout << it << ' ';
    }
    dark::dout << '\n';
    for(auto it : b) {
        dark::dout << it << ' ';
    }
    
    // int *ptr = new int[10];
    return 0;
}