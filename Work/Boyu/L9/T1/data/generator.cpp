#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

inline int rand_in(int a,int b) {
    return abs(rand() << 16 | rand()) % (b - a + 1) + a;
}

int a[] = {1,2,3,4,5,
           10,100,1000,1000,5000};
int b[] = {10,10,10,10,100,
           100,1000,5000,10000,10000};

signed main() {
    srand(time(NULL));
    vector <int> vec;
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        vec.clear();
        int n = rand_in(a[i - 1],b[i - 1]); 
        for(int i = 0 ; i < n ; ++i)
            vec.push_back(rand() * rand() * rand());
        freopen(in.c_str(),"w",stdout);
        dark::writeline(n);
        dark::writeRange(vec.begin(),vec.end());
        freopen(out.c_str(),"w",stdout);
        dark::writeRange(vec.rbegin(),vec.rend());
    }
    return 0;
}