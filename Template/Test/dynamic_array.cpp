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
    dynamic_array <std::string> d,t;
    t.push_back("1","2","3");
    d.push_back("2");
    d.copy_range(t.begin(),t.end());
    for(std::string &iter : d) std::cout << iter << ' ';
    std::cout << '\n';
    d = dynamic_array <std::string> {"a","b","c"};
    d = std::move(t);
    t = std::move(d);
    for(std::string &iter : d) std::cout << iter << ' ';
    std::cout << '\n';
    d.push_back("abc");
    d.emplace_back("66");
    d.push_back("13221");
    for(auto iter = d.rbegin() ; iter != d.crend() ; ++iter) {
        std::cout << *iter << ' ';
    }
    return 0;
}