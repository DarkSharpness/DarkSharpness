// #include <bits/stdc++.h>
// #pragma GCC optimize(3)

#include <Dark/memleak>
#include <Dark/inout>
#include <Dark/Container/map.h>
#include <map>

void print(dark::map &map) {
    // for(auto &iter : map)
        // dark::writeline(iter.first , iter.second.c_str() )
        ;
    puts("End"); 
}


signed main() {
    dark::map map;
    // std::map <int,std::string> t;
    // std::map <int,std::string> map = std::map <int,std::string>(t);

    srand(time(NULL));
    // std::pair <int,std::string> p = std::pair <int,std::string> (1,"5");
    auto t1 = clock();

    for(int i = 0 ; i < 2e5 ; ++i) {
        map.insert({rand() + rand() + rand(),"666"}); /* Debug test passed. */
        // map.check();
        if(map.erase(rand() + rand() + rand()));
        if(map.erase(rand() + rand() + rand()));
        if(map.erase(rand() + rand() + rand()));
        if(map.erase(rand() + rand() + rand()));
        // if(map.erase(rand() + rand() + rand()));
        // if(map.erase(rand() + rand() + rand()));


            // dark::writeline("");
        // map.check();
    }

    dark::writeline(clock() - t1);
    // dark::writeline(map.size());
    // map.erase(1);
    return 0;
}