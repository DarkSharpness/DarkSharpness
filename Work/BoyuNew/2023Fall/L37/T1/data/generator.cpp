#include <bits/stdc++.h>
using namespace std;

int a[13];

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";

        freopen(in.c_str() , "w" , stdout);
        std::cout << i << '\n';
        freopen(out.c_str() , "w" , stdout);        

        std::ranges::copy(std::ranges::iota_view(1,i + 1),a);
        do {
            std::ranges::copy(a,a + i,std::ostream_iterator<int>(std::cout," "));
            std::cout << '\n';
        } while(std::ranges::next_permutation(a,a + i).found);
    }
    return 0;
}
