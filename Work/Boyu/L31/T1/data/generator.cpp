#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

std::vector <int> ans;
std::deque  <int> d;

void generate(int n) {
    static int last;
    int x = rand() % 6 + 1;
    if(d.empty()) x = x % 2 + 1;
    if(x == 5 && last == 5) x = 6;
    if(x == 6 && last == 6) x = 5;
    dark::write(x);
    switch(x) {
        case 1:
            d.push_front(n);
            dark::printline(' ',n);
            break;
        case 2:
            d.push_back(n);
            dark::printline(' ',n);
            break;
        case 3:
            d.pop_front();
            dark::writeline();
            break;
        case 4:
            d.pop_back();
            dark::writeline();
            break;
        case 5:
            ans.push_back(d.front());
            dark::writeline();
            break;
        case 6:
            ans.push_back(d.back());
            dark::writeline();
            break;
    }
    last = x;
}


signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 1 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        const int n = i * i * i * 100 - 90;
        d.clear();
        ans.clear();
        freopen(in.data(),"w",stdout);
        dark::writeline(n);
        for(int i = 1 ; i <= n ; ++i)
            generate(i);
        freopen(out.data(),"w",stdout);
        for(auto x : ans)
            dark::writeline(x);
    }
    return 0;
}
