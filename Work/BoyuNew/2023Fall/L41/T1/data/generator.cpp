#include <bits/stdc++.h>
using namespace std;


int a[1003];

signed main() {
    srand(time(NULL));
    for (int i = 1 ; i <= 10 ; ++i) {
        ofstream in (std::format("{}.in",i));
        ofstream out(std::format("{}.out",i));

        const int n = i * i * 10;
        std::ranges::copy(std::views::iota(1, n + 1)| std::views::common, a + 1);
        std::ranges::shuffle(a + n / 2, a + n + 1, std::mt19937(std::random_device{}()));
        std::ranges::reverse(a + 1, a + n + 1);

        const int m = std::log10(n) + 1;
        for (int i = 1 ; i <= n ; ++i)
            if (rand() % m == 0)
                std::swap(a[i], a[rand() % n + 1]);

        in << n << '\n';
        for (int i = 1 ; i <= n ; ++i) in << a[i] << " \n"[i == n];
    }
    return 0;
}