#include <bits/stdc++.h>
using namespace std;


signed main() {
    std::array <int, 10> a;
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        ofstream fin (std::format("{}.in", i));
        ofstream fout(std::format("{}.out", i));
        int n = (i + 4) / 2;
        while (n < 7 && (rand() & 1)) ++n;

        fin << n << '\n';

        std::ranges::copy(std::ranges::iota_view(1, n + 1), a.begin());
        std::ranges::shuffle(a.begin(), a.begin() + n, std::mt19937(std::random_device()()));
        std::ranges::copy(a.begin(), a.begin() + n, std::ostream_iterator<int>(fin, " "));

        fin << '\n';

        std::ranges::shuffle(a.begin(), a.begin() + n, std::mt19937(std::random_device()()));
        std::ranges::copy(a.begin(), a.begin() + n, std::ostream_iterator<int>(fin, " "));

        fin << '\n';
    }
    return 0;
}
