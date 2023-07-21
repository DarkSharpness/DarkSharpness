#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

struct node {
    int value;
    int index;

    friend auto operator <=> (const node &lhs,const node &rhs) = default;
} t[1024];

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        const int n = std::max((1 << i),5 * i);
        for(int i = 0 ; i < n ; ++i)
            t[i] = {rand() % n + 1,i};
        freopen(in.data(),"w",stdout);
        dark::writeline(n);
        for(int i = 0 ; i < n ; ++i)
            dark::print(t[i].value,' ');
        freopen(out.data(),"w",stdout);
        sort(t,t + n);
        for(int i = 0 ; i < n ; ++i)
            dark::print(t[i].index,' ');
    }
    return 0;
}