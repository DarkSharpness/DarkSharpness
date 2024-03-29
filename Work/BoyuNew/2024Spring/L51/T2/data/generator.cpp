#include <format>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

std::size_t my_rand() {
    return (std::size_t)rand() * (RAND_MAX + 1) + rand();
}


std::vector <int> generate(int __n) {
    std::vector <int> ret(__n + 1);

    ret[1] = 0;
    for (int i = 2 ; i <= __n ; ++i) ret[i] = my_rand() % (i - 1) + 1;

    std::vector <int> perm(__n + 1);
    for (int i = 1 ; i <= __n ; ++i) perm[i] = i;
    std::random_shuffle(perm.begin() + 1, perm.end());

    std::vector <int> ans(__n + 1);
    for (int i = 0 ; i <= __n ; ++i)
        ans[perm[i]] = perm[ret[i]];
    return ans;
}


signed main() {
    // Fixed random seed
    srand(435834796);
    const int num[] = {
        0, 1, 100, 1000, 10000,
        (int)1e5, (int)2e5, (int)4e5, (int)6e5, (int)8e5, (int)1e6 
    };
    for (int i = 1 ; i <= 10 ; ++i) {
        std::fstream in  (std::format("{}.in", i), std::ios::out);
        std::fstream out (std::format("{}.out", i), std::ios::out);
        
        const int n = num[i];
        std::vector <int> ans = generate(n);

        in << n << '\n';
        for (int i = 1 ; i <= n ; ++i)
            in << ans[i] << " \n"[i == n];
    }
    return 0;
}
