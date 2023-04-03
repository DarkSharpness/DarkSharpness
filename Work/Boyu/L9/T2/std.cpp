#include <iostream>
using namespace std;

int middle(int x,int y,int z) {
    int maxn;
    if(x > y)    maxn = x;
    else         maxn = y;
    if(z > maxn) maxn = z;
    int minn;
    if(x < y) minn = x;
    else      minn = y;
    if(z < minn) minn = z;
    return x + y + z - maxn - minn;
}


signed main() {
    int x,y,z;
    cin >> x >> y >> z;
    cout << middle(x,y,z);
    return 0;
}
