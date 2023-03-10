// #include <bits/stdc++.h>
#pragma GCC optimize(3)

#include <Dark/memleak>
#include <Dark/inout>
#include <Dark/Container/map.h>
#include <map>


struct test {};
inline void func() {
    auto t1 = clock();
    for(int i = 0 ; i < 1e6 ; ++i) (rand() + rand() + rand());
    auto t0 = clock() - t1;

    std::pair <int,test> p(3,{});

    // dark::map <int,test> map;
    std::map <int,test> map;
    srand(time(NULL));

    t1 = clock();

    for(int i = 0 ; i < 1e6 ; ++i) {
        p.first = rand() + rand() + rand();
        map.insert(p); /* Debug test passed. */
    }
    dark::write(clock() - t1 - t0,"");

    t1 = clock();
    for(int i = 0 ; i < 1e6 ; ++i) {
        map.erase(rand() + rand() + rand()); /* Debug test passed. */
    }
    dark::write(clock() - t1 - t0,"");

    map.clear();

    t1 = clock();
    for(int i = 0 ; i < 5e5 ; ++i) {
        p.first = rand() + rand() + rand();
        map.insert(p); /* Debug test passed. */
        map.erase(rand() + rand() + rand()); /* Debug test passed. */
    }
    dark::writeline(clock() - t1 - t0 * 2);
}

signed main() {
    int n = 1;
    // freopen("map0.txt","a",stdout);
    while(n--) func();
    return 0;
}