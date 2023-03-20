#include <iostream>
using namespace std;


signed main() {
    long long a,b,n;
    cin >> a >> b >> n;
    if(n == 1) cout << a;
    else {
        int i = 2;
        while(i != n) {
            long long c = b + a;
            if(i % 2) ++c;
            a = b;
            b = c;
            ++i;
        }
        cout << b;
    }
    return 0;
}
