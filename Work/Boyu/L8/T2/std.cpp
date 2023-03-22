#include <iostream>
using namespace std;


signed main() {
    int n;
    cin >> n;
    bool flag = false;
    for(int i = 2 ; i < n ; ++i)
        if(n % i == 0) {
            flag = true;
            break;
        }
    if(flag == true) cout << "No";
    else cout << "Yes";
    return 0;
}
