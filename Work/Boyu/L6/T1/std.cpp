#include <iostream>
using namespace std;

signed main() {
    int a = 0,b = 0,c = 0;
    unsigned long long t;
    cin >> t;
    while(t) {
        if(t % 3 == 0) ++a;
        else if(t % 3 == 1) ++b;
        else ++c;
        t /= 3;
    }
    cout << a << ' ' << b << ' ' << c;
    return 0;
}
