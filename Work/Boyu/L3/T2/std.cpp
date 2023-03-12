#include <iostream>
using namespace std;

signed main() {
    float x,y,z;
    cin >> x >> y >> z;
    float t = x;
    if(t < y) t = y;
    if(t < z) t = z;
    t = x + y + z - 2 * t; 
    if(t < 0.0001 && t > -0.0001) cout << "YES";
    else cout << "NO";
    return 0;
}
