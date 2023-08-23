#include <iostream>
using namespace std;


signed main() {
    char c;
    int n;
    cin >> n;
    int a = 0,b = 0;
    while(n--) {
        cin >> c;
        if(c >= 'a' && c <= 'z') ++a;
        if(c >= 'A' && c <= 'Z') ++b;
    }
    cout << a << '\n' << b;
    return 0;
}
