// #include <bits/stdc++.h>
// #pragma GCC optimize(3)

#include <Dark/memleak>
#include <Dark/inout>
#include "Lite_map.h"
#include <map>

struct test {};
void check(dark::map <int,test> &mp) {
    int last = 0;
    for(auto &&iter : mp)
        if(iter.first <= last) throw 1919810;
}


signed main() {
    // freopen("map0.txt","a",stdout);
    // srand(time(NULL));
    using map = dark::map <int,int>;
    map m;
    // m.insert({0,1});
    for(int i = 0 ; i < 2 ; ++i) {
        m.insert({i,i});
        // m.check();
        // size_t cnt = 0;
        // for(auto &&iter : m) { cnt += iter.first * 0 + 1; }
        // if(cnt != m.size()) dark::writeline("Wrong!\n");
        // if(m.begin() == m.end()) dark::writeline(i);
    }

    size_t count = m.size();
    dark::writeline(count);
    dark::writeline("Rest in peace");
    system("pause");

    auto copy = map(m);
    m.clear();

    size_t tot = 0;
    for(auto &&iter : copy)
        if(iter.first != iter.second) throw;
        else ++tot;
    dark::writeline(tot);

    m = copy;
    size_t cnt = 0;

    for(auto &&iter : m)
        if(iter.first != iter.second) throw;
        else ++cnt;
    
    dark::writeline(cnt);

    map empty;
    auto iter = empty.begin();
    // --empty.begin();
    // --m.begin();
    // m.check();
    // m.clear();

    // while(m.begin() != m.end()) m.erase(m.begin());

    // for(int i = 0 ; i < count ; ++i) {
    //     // dark::writeline(i);
    //     // dark::writeline(m.begin() == m.end() ? "True" : "False");
    //     m.erase(m.begin());
    //     // m.check();
    //     // size_t cnt = 0;
    //     // for(auto &&iter : m) { cnt += iter.first * 0 + 1; }
    //     // if(cnt != m.size()) dark::writeline("Wrong!\n",cnt,m.size());
    // }

    // dark::writeline(m.size(),int(m.empty()));



    // m[0] = 3;
    // m[1] = 2;
    // m[3] = 5;
    // m[2] = 1;
    // for(auto && iter : m) dark::writeline(iter.first,iter.second);
    // dark::map <int,int>::iterator a;
    return 0;
}