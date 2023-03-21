#include <iostream>
using namespace std;


signed main() {
    int n;
    cin >> n;
    int sum = 0,max1 = 0,max2 = 0,min1 = 10000,min2 = 10000;
    while(n--) {
        int x;
        cin >> x;
        sum += x;
        if(x > max1) {
            max2 = max1;
            max1 = x;
        } else if(x > max2) {
            max2 = x;
        }

        if(x < min1) {
            min2 = min1;
            min1 = x;
        } else if(x < min2) {
            min2 = x;
        }
    }
    cout << max1 << ' ' << max2 << '\n';
    cout << min1 << ' ' << min2 << '\n';
    cout << sum;
    return 0;
}
