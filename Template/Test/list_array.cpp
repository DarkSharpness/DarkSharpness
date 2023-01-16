#include <iostream>
#include <Dark/memleak>
#include <Dark/list_array>
#include <Dark/any>

using dark::list_array;
using dark::Any;

signed main() {
    list_array <Any> tmp(3,2);
    tmp.assign(3,0);
    tmp.push_front(1);
    tmp.push_back(3,5);
    tmp.emplace_front(-1);
    tmp.emplace_back(6);
    tmp.resize_back(9,1);
    tmp.resize_front(10,114514);

    std::cout << tmp.size() << '\n';
    for(auto &it : tmp) std::cout << int(it) << ' ';
    std::cout << '\n';


    tmp.pop_back(2);
    tmp.pop_front(2);
    tmp.resize_back(5);
    tmp.resize_front(4);
    std::cout << tmp.size() << '\n';
    
    list_array <Any>::iterator iter;
    iter = tmp.begin();
    iter[0] = int(*--tmp.cend()) - 1;


    tmp = 1.5 * (tmp * 2);
    tmp.pop_front(4);
    tmp += list_array <Any> {1,2,3};

    iter = tmp.begin();
    iter[0] = iter[1].as <int> () + 1;

    for(auto &it : tmp) std::cout << int(it) << ' ';
    tmp.clear();

    
    return 0;
}