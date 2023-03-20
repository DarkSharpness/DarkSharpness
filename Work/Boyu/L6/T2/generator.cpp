#include <bits/stdc++.h>
#include <Dark/inout>
// #define int long long
// using ll = long long;
// using ull = unsigned long long;
using namespace std;

const int N = 10003;
long long dp[N];

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        freopen("CON","w",stdout);
        string in  = to_string(i) + ".in" ;
        string out = to_string(i) + ".out"; 
        int n;
        cin >> dp[1] >> dp[2];
        while(cin >> n && n) {
            for(int i = 3 ; i <= n ; ++i) {
                dp[i] = dp[i - 1] + dp[i - 2];
                if(i % 2 == 0) ++dp[i];
            }
            cout << dp[n] << '\n';
        }
        cout << "Final" << '\n';
        cin >> n;
        freopen(in.c_str() ,"w",stdout);
        cout.clear();
        cout << dp[1] << ' ' << dp[2] << ' ' << n;
        freopen(out.c_str(),"w",stdout);
        cout.clear();
        cout << dp[n] << '\n';
    }
    return 0;
}