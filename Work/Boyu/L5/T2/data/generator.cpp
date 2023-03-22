#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;


signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        freopen(in.c_str(),"w",stdout);
        double x = double(rand()) * rand() * rand() / rand() / rand(); 
        double y = double(Wrand()) * rand() * rand() / rand() / rand(); 
        if(rand() % 3 == 0) y = x;
        dark::write(x,y);
        freopen(out.c_str(),"w",stdout);
        dark::write(x == y ? "Yes" : "No");
    }
    return 0;
}
