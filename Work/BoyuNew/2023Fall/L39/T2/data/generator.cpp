#include <bits/stdc++.h>
using namespace std;


signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        ofstream in (std::format("{}.in",i));
        ofstream out(std::format("{}.out",i));
        const int n = i * i * i * 100;
        in << n << '\n';
    }
    return 0;
}
