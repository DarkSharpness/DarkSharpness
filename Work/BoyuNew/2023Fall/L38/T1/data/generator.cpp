#include <bits/stdc++.h>
#include "helper.h"
using namespace std;


signed main() {
    srand(time(NULL));
    std::vector <int> loc;
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        
        const int b = rand() % (i * i * 3) + 2 * i * i + 1;
        if (b > 500 || b < 2) throw;

        make_map(b);

        freopen(in.c_str(),"w",stdout);
        const int n = 2 * b - 1;
        std::cout << n << " " << n << "\n";
        print_map(n);
    }
    return 0;
}