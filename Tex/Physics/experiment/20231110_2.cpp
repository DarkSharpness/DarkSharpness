#include <bits/stdc++.h>

using data_t = std::array <double,6>;

data_t I[3][6];
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

    const double C = 2.99e14 / std::pow(4, 2 - (flag >> 1));

    const double e_m = C * U / (1306 * 1306 * avg * avg);

    const double e_m_r = 2 * ur;

    std::cout << std::format(
        "e/m = {:.3e} ± {:.3e} C/kg \t"
        "ur = {:.1f}% \n",
        e_m, e_m_r * e_m / 100, e_m_r
    );

    std::cout << "----------------\n";
}

signed main() {
    freopen("20231110_2.txt", "w", stdout);
    std::ifstream fin("x.txt");
    for (int i = 0 ; i < 6 ; ++i) work(fin, I[0][i] , i);
    return 0;
}