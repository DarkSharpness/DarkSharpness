#include <iostream>
using namespace std;


signed main() {
    int n;
    cin >> n;
    while(n--) {
        int x,y;
        cin >> x >> y;
        /* 保证 x < y */
        if(y < x) { int t = x; x = y ; y = t; }
        for(int i = x ; /* 想想为啥不用写终止条件 */ ; --i)
            if(y % i == 0 && x % i == 0) {
                cout << i << '\n';
                break;
            }
    }
    return 0;
}