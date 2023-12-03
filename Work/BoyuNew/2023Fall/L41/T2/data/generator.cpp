#include <bits/stdc++.h>
using namespace std;

bool t[4][4];


signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        ofstream in (std::format("{}.in",i));
        ofstream out(std::format("{}.out",i));
        const int n = i * i * 10;
        const int m = i * i * 100;

        in << n << ' ' << m << '\n';
        const int sqr = sqrt(n);
        const int log = log2(n);
        const int mod = i * i * 150;

        vector <int> v;

        for (int i = 1 ; i <= sqr ; ++i)
            v.push_back((rand() ^ rand() << 8) % (i + 1) + 1);
        for (int i = sqr + 1 ; i < n - log ; ++i)
            v.push_back((rand() ^ rand() << 8) % sqr + 1);
        for (int i = n - log ; i <= n ; ++i)
            v.push_back((rand() ^ rand() << 8) % mod + 1);

        std::ranges::sort(v, greater<int>());
        if (i == 2) // filter out all odd numbers
            std::ranges::transform(v, v.begin(), [](int x) { return x + (x & 1); });
        std::ranges::shuffle(v.begin(), v.end(), std::mt19937(std::random_device()()));
        std::ranges::copy(v, ostream_iterator<int>(in, " "));
    }
    return 0;
}
