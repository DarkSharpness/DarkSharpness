// #include <bits/stdc++.h>
#include "Lite_vector.h"
#include <Dark/memleak>

template <class T>
void print(T &tmp) {
    std::cout << "Size:" << tmp.size() << " Capacity:" << tmp.capacity() << '\n';
    for(auto &it : tmp)
        std::cout << it << ' ';
    std::cout << '\n';
}

signed main() {
    dark::dynamic_array <int> d = {1,3,4};
    d.push_back(2,10);
    // d.resize(10);
    d.insert(d.end(),-2);
    d.insert(d.begin(),-1);
    d.erase(d.begin());
    d.pop_back();
    // while(!d.empty()) d.erase(d.begin());
    print(d);

    sjtu::vector <int> v;
    v.push_back(1,2,3);
    print(v);

    // d.pop_back();
    // auto iter = ++d.begin();
    return 0;
}