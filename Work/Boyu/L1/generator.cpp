// This is a generator for data.
#include <bits/stdc++.h>
using namespace std;

const char mp[] = {
'q','w','e','r','t','y','u','i','o','p','a',
's','d','f','g','h','j','k','k','l',
'z','x','c','v','b','n','m',
'1','2','3','4','5','6','7','8','9','_'
};


signed main() {
    int n;
    int count = 0;
    char name[] = "7.in";
    while(cin >> n && ++count != 10) {
        ++name[0];
        freopen(name,"w",stdout);
        for(int i = 0 ; i < n ; ++i) {
            putchar(mp[abs(rand()) % sizeof(mp)]);
            if(abs(rand()) % (n << 2) == 0) 
                putchar('0'),++i;
        }
        putchar('0');
    }
    return 0;
}