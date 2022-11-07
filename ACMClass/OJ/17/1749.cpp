#include<bits/stdc++.h>
using namespace std;

const auto func = [](const int &n) -> void {
    bitset <14> mp[14];
    bitset <14> col;
    bitset <14 * 2> a;
    bitset <14 * 2> b;
    int depth = 0,cur[14];
    memset(cur,0,sizeof(14));
    while(true) {
        #define x cur[depth]
        #define y depth
        while(x == n) {
            
        }
        if(depth < 0) break;
        if(depth == n) { // Output
            for(int i = 0 ; i < n ; ++i) {
                for(int j = 0 ; j < n ; ++j) {
                    if(mp[i][j]) putchar('Q');
                    else putchar('.');
                }
                putchar('\n');
            }
            ++cur[--depth];
            break;
        }
        
        do {
            if(a[x+y] || b[x-y+n])

        } while(cur[depth] <= n);
    }


};

int main() {
   int n;
   cin >> n;
   func(n);
   return 0;
}