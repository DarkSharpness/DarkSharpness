/* 不要抄题解!!!!!!!!!! */
#include <iostream>
using namespace std;

const int N = 1003;
int n,m;
int a[N];
int d[N];


signed main() {
    cin >> n >> m;
    for(int i = 1 ; i <= m ; ++i) cin >> a[i];    
    d[0] = 1;
    for(int i = 1 ; i <= n ; ++i) {
        for(int j = 1 ; j <= m ; ++j) {
            if(i < a[j]) continue;
            else d[i] += d[i - a[j]];
        }
    } 
    cout << d[n];
    return 0;
}