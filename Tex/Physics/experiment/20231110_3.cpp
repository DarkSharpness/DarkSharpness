#include <bits/stdc++.h>

using data_t = struct : std::array <double,6> {
    double val;
};

void work(std::ifstream &fin, data_t &I, int flag) {
    double sum = 0;
    for (auto &__val : I) { fin >> __val; sum += __val; }

    const double avg = sum / I.size();

    double sqr = 0;
    for (auto &__val : I) { sqr += (__val - avg) * (__val - avg); }

    const double sigma = std::sqrt(sqr / (I.size() - 1));

    const double delta = 1.05 * sigma;

    const double u = std::sqrt(delta * delta);

    const double ur = u / avg * 100;

    std::cout << std::format(
        "I  = {:.3f} ± {:.3f} A \t"
        "ur = {:.1f}% \n",
        avg, u, ur
    );

    const double U = (flag & 1) * 100 + 850;

    I.val = U / (1336 * 1306 * std::pow(4, 2 - (flag >> 1)) * avg * avg);
    std::cout << std::format("e/mC = {:.3e} V/A^2\n", I.val);
}

signed main() {
    freopen("20231110_3.txt", "w", stdout);
    std::ifstream fin("y.txt");
    data_t I;
    for (int i = 0 ; i < 6 ; ++i) work(fin, I , i);
    return 0;
}