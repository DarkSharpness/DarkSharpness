#include <iostream>
using namespace std;


int main() {
    long long a,x,y;
    cin >> a >> x >> y;
    if (x > 99) {
        std::cout << 1;
        return 0;
    }

    long long l = 1,r = y;
    while (l != r) {
        long long mid = (l + r) >> 1;
        long long last[2];
        last[0] = a;
        last[1] = mid;
        for(int i = 3 ; i <= x ; ++i) {
            long long z = last[0] + last[1];
            last[0] = last[1];
            last[1] = z;
            if (z >= y) break;
        }
        if (last[1] >= y) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    std::cout << l;
    return 0;
}