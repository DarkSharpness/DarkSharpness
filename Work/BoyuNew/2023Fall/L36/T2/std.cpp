#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int ans = 0,x;
    while(n--) {
        cin >> x;
        ans ^= x;
    }
    cout << ans << '\n';
    return 0;
}