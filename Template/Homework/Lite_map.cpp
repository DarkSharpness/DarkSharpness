#pragma GCC optimize(3)

#include <Dark/memleak>
#include <Dark/inout>
#include "Lite_map.h"
#include <map>


struct test {};
inline void func() {
    auto t1 = clock();
    for(int i = 0 ; i < 1e6 ; ++i) (rand() + rand() + rand());
    auto t0 = clock() - t1;

    sjtu::pair <int,test> p(3);

    // std::pair <int,test> p(3,{});

    dark::map <int,test> map;
    // std::map <int,test> map;
    srand(time(NULL));

    t1 = clock();

    for(int i = 0 ; i < 1e6 ; ++i) {
        p.first = rand() + rand() + rand();
        map.insert(p); /* Debug test passed. */
    }
    dark::write(clock() - t1 - t0,"");
    for(auto &&iter : map);

    t1 = clock();
    for(int i = 0 ; i < 1e6 ; ++i) {
        map.erase(rand() + rand() + rand()); /* Debug test passed. */
    }
    dark::write(clock() - t1 - t0,"");
    for(auto &&iter : map);

    map.clear();

    t1 = clock();
    for(int i = 0 ; i < 5e5 ; ++i) {
        p.first = rand() + rand() + rand();
        map.insert(p); /* Debug test passed. */
        map.erase(rand() + rand() + rand()); /* Debug test passed. */
    }
    dark::writeline(clock() - t1 - t0 * 2);
    for(auto &&iter : map);
}

signed main() {
    int n = 0;
    while(n--) func();
    dark::map <int,int> map;
    // map[1] = 2;
    // map[2] = 1;
    sjtu::pair <int,int> p = {1,2};
    map.insert(p);
    map.insert(2,3);
    map.at(2) = 1;
    // map.insert(p);
    for(auto &iter : map) dark::writeline(iter.first,iter.second);

    for(auto iter = map.rbegin() ; iter != map.rend() ; ++iter)
        dark::writeline(iter->first,iter->second);
    return 0;
}
