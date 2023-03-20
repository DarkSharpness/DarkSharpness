#include <bits/stdc++.h>
// #include <Dark/inout>
// #define int long long
// using ll = long long;
// using ull = unsigned long long;
using namespace std;


signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string I = to_string(i) + ".in" ;
        string O = to_string(i) + ".out";
        freopen(I.c_str(),"w",stdout);
        cout.clear();
        int a,b,c,d;
        cout << (a = rand() % 201 - 100) << ' '
             << (b = rand() % 201 - 100) << ' '
             << (c = rand() % 201 - 100) << ' '
             << (d = rand() % 201 - 100);
        freopen(O.c_str(),"w",stdout);
        cout.clear();
        int sum = a + b + c + d;
        if(sum > 0) cout << "Larger than 0";
        else if(!sum) cout << "Exactly 0";
        else cout << "Smaller than 0";
    }
    return 0;
}