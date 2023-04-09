#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

const int N = 101;
int a[N];


signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        freopen(in.c_str(),"w",stdout);
        int n = rand() % N + 1;
        dark::writeline(n);
        for(int i = 1 ; i <= n ; ++i) a[i] = (rand() % 201) - 100;
        dark::writelineRange(a + 1,a + n + 1);
        for(int i = 1 ; i <= n ; ++i) a[i] += a[i - 1];
        vector <int> ans;
        int q = rand() % N + 1;
        while(q--) {
            int l = rand() % n + 1;
            int r = rand() % n + 1;
            if(l > r) swap(l,r);
            dark::writeline(l,r);
            ans.push_back(a[r] - a[l - 1]);
        }
        freopen(out.c_str(),"w",stdout);
        dark::writelineRange(ans.begin(),ans.end());   
    }
    return 0;
}