#include <iostream>
using namespace std;

signed main() {
    int a,b,c,d;
    cin >> a >> b >> c >> d;
    int sum = a + b + c + d;
    if(sum > 0) cout << "Larger than 0";
    else if(!sum) cout << "Exactly 0";
    else cout << "Smaller than 0";
    return 0;
}
