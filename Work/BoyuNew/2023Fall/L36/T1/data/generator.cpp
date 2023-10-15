#include <bits/stdc++.h>
using namespace std;

const int N = 5003;
std::array <int, N> a;


signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";

        const int n = 50 * i * i;
        const int w = rand() % (n - 10) + 10;

        const int t = rand() % (n >> 1) + 1; // 有 t 个人是两个人一艘船
        auto *p = a.begin();


        for(int i = 0 ; i < t ; ++i) {
            *p = rand() % (w >> 1) + 1;
            ++p;
            *p = w - *(p - 1);
            ++p;
        }

        const int r = n - (t << 1);                     // 剩下 r 个人是单独一艘船
        int c = (r + t > 5000) ? 5000 : (r + t);  // 总共有 c 艘船

        while(p != a.begin() + n)
            *p++ = rand() % (w / 4) + (w * 3 / 4) + 2; // may exceed w!

        std::cerr << t << ' ' << r << '\n';

        random_shuffle(a.begin(),a.begin() + n);
        freopen(in.data(),"w",stdout);

        cout << n << ' ' << w << ' ' << c << '\n';
        for(int i = 0 ; i < n ; ++i) cout << a[i] << ' ';
    }
    return 0;
}
