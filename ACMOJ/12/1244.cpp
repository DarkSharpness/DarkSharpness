#include <bits/stdc++.h>
using namespace std;


signed main() {
    long long x,y;
    cin >> x >> y;
    puts(x <= (y << 1) ? "Bob" : "Alice");
    return 0;
}