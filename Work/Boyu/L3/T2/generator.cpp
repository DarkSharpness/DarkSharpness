#include <bits/stdc++.h>
using namespace std;


signed main() {
    srand(time(NULL));
    char name[] = "2.in";
    for(int i = 0 ; i < 8 ; ++i) {
        freopen(name,"w",stdout);
        int a,b;
        cout << (a = rand()) << ' ' 
             << (b = rand()) << ' ';
        cout << a + b;
        ++name[0];
    }
    return 0;
}
