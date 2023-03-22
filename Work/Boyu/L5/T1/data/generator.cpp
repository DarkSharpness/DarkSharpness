#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

inline int sum(int x) { return x ? pow(x % 10,3) + sum(x / 10) : 0; }

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string I = to_string(i) + ".in" ;
        string O = to_string(i) + ".out";
        freopen(I.c_str(),"w",stdout);
        int x = rand() % 1000;
        dark::write(x);
        freopen(O.c_str(),"w",stdout);
        cout.clear();
        dark::write(x == sum(x) ? "Yes" : "No");
    }
    return 0;
}