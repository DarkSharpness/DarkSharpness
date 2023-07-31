#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

struct node {
    int value;
    int index;

    friend bool operator < (const node &lhs,const node &rhs) {
        if(lhs.value / 4 != rhs.value / 4)
            return lhs.value / 4 < rhs.value / 4;
        else
            return lhs.index < rhs.index;
    }
} t[1 << 16];

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        const int n = 1 << (i + 6);
        for(int i = 0 ; i < n ; ++i)
            t[i] = {rand() % n + 1,i};
        freopen(in.data(),"w",stdout);
        dark::writeline(n);
        for(int i = 0 ; i < n ; ++i)
            dark::print(t[i].value,' ');
        freopen(out.data(),"w",stdout);
        sort(t,t + n);
        for(int i = 0 ; i < n ; ++i)
            dark::print(t[i].value,' ');
    }
    return 0;
}