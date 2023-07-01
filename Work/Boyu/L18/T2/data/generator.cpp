#include <bits/stdc++.h>
#include <Dark/inout>

std::string ran() {
    std::string __ans;
    int __n = rand() % 10 + 40;
    __ans.reserve(__n + 1);
    __ans.push_back(rand() % 9 + '1');
    while(--__n) __ans.push_back(rand() % 10 + '0');
    return __ans;
}

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        std::string in  = std::to_string(i) + ".in";
        std::string out = std::to_string(i) + ".out";
        freopen(in.data(),"w",stdout);
        int n = rand() % (10 * i) + 1;
        dark::writeline(n);
        std::vector <std::string> vec;
        for(int i = 0 ; i != n ; ++i)
            vec.push_back(ran());
        for(auto &&iter : vec)
            dark::writeline(iter.data());
        freopen(out.data(),"w",stdout);
        std::sort(vec.begin(),vec.end(),[](const std::string &lhs,const std::string rhs) {
            if(lhs.size() != rhs.size()) return lhs.size() < rhs.size();
            return lhs < rhs;
        });
        for(auto &&iter : vec)
            dark::writeline(iter.data());
    }
    return 0;
}