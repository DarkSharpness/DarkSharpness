#include <iostream>
using namespace std;

void print(int n) {
    if(n == 0) return;
    cout << '+';
    print(n - 1);
}


signed main() {
    int n;
    cin >> n;
    print(n);
    return 0;
}