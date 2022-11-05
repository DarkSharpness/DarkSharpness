#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long

const int N = 114514;
int h[N];
int sqr[N]; // sqrt(i) in
inline void prework(int n) {
    int j = 1;
    for(int i = 1 ; i <= n ; ++i) {
        if(j * j < i) ++j;
        sqr[i] = j;
    }
}
    
int n;

/// @brief GetMinimum swap time of x,y (x < y) 
inline int getTime(int x,int y) {
    if(h[y] <= h[x]) return n + 1;            // y useless
    if(h[y] >= h[x] + sqr[y-x]) return y;     // x useless
    int l = y ,r = n + 1,ans = n + 1;
    while(l < r) { // Find the exact time
        int mid = (l + r) >> 1;
        if(h[y] + sqrt(double(mid-y)) >=
           h[x] + sqrt(double(mid-x)) ) {
            ans = r = mid;
        } else {
            l = mid + 1;    
        }
    }
    return ans;
}
signed main() {
    cin >> n;
    prework(n);
    for(int i = 1 ; i <= n ; ++i) cin >> h[i];
    int x,y;
    while(cin >> x >> y) {
        cout << getTime(x,y) << endl;
    }
    return 0;
}