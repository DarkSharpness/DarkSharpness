// This is a generator for data.
#include <bits/stdc++.h>
using namespace std;

const char mp[] = {
'1','2','3','4','5','6','7','8','9','0'
};


signed main() {
    int count = 0;
    char name[] = "0.in";
    while(++count != 6) {
        ++name[0];
        freopen(name,"w",stdout);
        cout << rand() << ' ' << rand();
    }
    return 0;
}
