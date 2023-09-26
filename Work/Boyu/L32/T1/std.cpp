#include <iostream>
#include <algorithm>
using namespace std;

const int N = 5e5 + 3;
int a[N];
int b[N];
int c[N];

signed main() {
    int n,m = 0;
    cin >> n;
    for(int i = 0 ; i < n ; ++i) {
        int x;
        cin >> x;
        while(x--) cin >> a[m++];
    }
    sort(a , a + m);
    int last = a[0];
    int cnt  = 1;
    int topb = 0;
    int topc = 0;
    for(int i = 1 ; i <= m ; ++i) {
        if(a[i] == last) ++cnt;
        else {
            c[topc++] = last;
            if(cnt == n) b[topb++] = last;
            cnt  = 1;
            last = a[i];
        }
    }
    for(int i = 0 ; i < topb ; ++i) cout << b[i] << ' ';
    std::cout << '\n';
    for(int i = 0 ; i < topc ; ++i) cout << c[i] << ' ';
    return 0;
}
