#include <iostream>
using namespace std;

signed main() {
    int n;
    cin >> n;
    while(n--) {
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        int sum = a + b + c + d;
        if(sum > 0) cout << "Larger than 0\n";
        else if(!sum) cout << "Exactly 0\n";
        else cout << "Smaller than 0\n";
    }
    return 0;
}
