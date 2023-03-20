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
        vector <string> ans;
        freopen(I.c_str(),"w",stdout);
        cout.clear();
        int n = rand() % 1000;
        cout << n << '\n';
        while(n--) {
            int a,b,c,d;
            cout << (a = rand() % 201 - 100) << ' '
                 << (b = rand() % 201 - 100) << ' '
                 << (c = rand() % 201 - 100) << ' '
                 << (d = rand() % 201 - 100) << '\n';
            int sum = a + b + c + d;
            if(sum > 0) ans.push_back("Larger than 0");
            else if(!sum) ans.push_back("Exactly 0");
            else ans.push_back("Smaller than 0");
        }
        cout.clear();
        freopen(O.c_str(),"w",stdout);
        for(auto && iter : ans)
            cout << iter << '\n';
    }
    return 0;
}