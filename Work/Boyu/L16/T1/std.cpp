#include <iostream>
using namespace std;
const int N = 102;

struct node {
    int length;
    int data[N];
} t[N];


signed main() {
    int n;
    cin >> n;
    for(int i = 1 ; i <= n ; ++i) {
        cin >> t[i].length;
        for(int k = 1 ; k <= t[i].length ; ++k)
            cin >> t[i].data[k];
    }

    int q;
    cin >> q;
    int ans = 1,maxn = -N;
    if(q <= t[1].length) maxn = -t[1].length;
    for(int i = 2 ; i <= n ; ++i)
        if(q <= t[i].length && t[i].data[q] > maxn)
            ans = i,maxn = t[i].data[q];
    cout << ans;
    return 0;
}
