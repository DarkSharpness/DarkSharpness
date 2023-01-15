#include <Dark/memleak>
#include <Dark/dynamic_array>
#include <Dark/any>
#include <iostream>

using dark::dynamic_array;
using dark::Any;

void test(Any &a) {
    if(a.is <int> ())       std::cout << "int\n";
    if(a.is <long long> ()) std::cout << "long long\n";
    if(a.isNull())          std::cout << "nullptr\n";
}

signed main() {
    dynamic_array <Any> d(3,nullptr);
    d.pop_back();
    d.push_back(1);
    d.back() = 0;
    for(auto &it : d) test(it);

    dynamic_array <dynamic_array <int>> t;
    dynamic_array <int> tmp{1,2,3};
    t.push_back(tmp);
    t.pop_back();
    t.push_back(tmp);
    tmp.pop_back();
    t.push_back(tmp);
    for(auto &it1 : t) {
        for(auto &it2 : it1) {
            std::cout << it2 << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}