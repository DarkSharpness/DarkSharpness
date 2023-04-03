#include <iostream>
using namespace std;
const int M = 101;
int cnt[M];

signed main() {
    int n;
    cin >> n;
    for(int i = 0,x ; i < n ; ++i) {
        cin >> x;
        ++cnt[x];
    }
    int loc = 0;
    cnt[0] = 0;
    for(int i = 1 ; i <= 100 ; ++i)
        if(cnt[i] >= cnt[loc]) loc = i;
    cout << loc;
    return 0;
}
