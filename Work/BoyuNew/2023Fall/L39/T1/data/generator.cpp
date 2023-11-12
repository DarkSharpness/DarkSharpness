#include <bits/stdc++.h>
using namespace std;

const long long mod = 1e9 + 7;

signed main() {
    srand(time(NULL));
    std::vector <int> loc;
    std::vector <int> vec;
    for (int i = 1 ; i <= 10 ; ++i) {
        ofstream in (std::format("{}.in",i));
        ofstream out(std::format("{}.out",i));

        const int m = i * i * 100;
        const int k = rand() % (m / 2) + 1;

        loc.clear();
        std::ranges::copy(std::ranges::views::iota(1, m + 1), std::back_inserter(loc));
        std::random_shuffle(loc.begin(), loc.end());

        vec.clear();
        std::ranges::copy(loc | std::ranges::views::take(k), std::back_inserter(vec));
        std::random_shuffle(vec.begin(), vec.end());

        in << std::format("{} {}\n", m, k);
        std::ranges::copy(vec, std::ostream_iterator <int> (in, " "));
        in << '\n';
        std::ranges::copy(loc, std::ostream_iterator <int> (in, "\n"));

        vec.reserve(m + 1);
        for (int j = k ; j <= m ; ++j) {
            long long sum = 0;
            for (int l = 1 ; l <= k ; ++l) sum += vec[j - l];
            vec.push_back(sum % mod);
        }

        for (auto x : loc) out << vec[x - 1] << '\n';
    }
    return 0;
}