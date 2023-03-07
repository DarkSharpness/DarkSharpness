// #include <bits/stdc++.h>
#include <Dark/memleak>
#include <Dark/inout>
#include <Dark/Container/map.h>

void print(dark::map &map) {
    for(auto &iter : map) 
        // dark::writeline(iter.first , iter.second.c_str() )
        ; 
}


signed main() {
    dark::map map;
    print(map);
    for(int i = 0 ; i < 5e5 ; ++i) 
        map.insert({rand() | rand() << 16,"a"}); /* Debug test passed. */
    print(map);
    // map.erase(1);
    return 0;
}