#include <bits/stdc++.h>

using data_t = struct : std::array <double,6> {
    double avg, sigma, delta, u, ur;
};

data_t I[3][6];
void work(std::ifstream &fin, data_t &I) {
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
    I.avg = avg;
    I.sigma = sigma;
    I.delta = delta;
    I.u = u;
    I.ur = ur;
}

signed main() {
    freopen("20231110.txt", "w", stdout);
    std::ifstream fin[3];

    fin[0].open("850.txt");
    fin[1].open("900.txt");
    fin[2].open("950.txt");


    constexpr double D = 0.095;
    constexpr double L = 0.240;
    constexpr double x = 0.199 / 2;

    const double K = 1e14 * L * L / (
        2 * (
            std::sqrt(D * D / 4 + (L / 2 + x) * (L / 2 + x)) 
        -   std::sqrt(D * D / 4 + (L / 2 - x) * (L / 2 - x)) 
        )
    );
    std::cout << std::format("K  = {:.3f} \n\n", K);

    for (int j = 0 ; j < 3 ; ++j) {
        for (int i = 0 ; i < 3 ; ++i) work(fin[j],I[j][i]);
        for (int i = 3 ; i < 6 ; ++i) work(fin[j],I[j][i]);
        std::cout << '\n';

        double _I = 0;
        for (auto &__val : I[j]) _I += __val.avg;
        _I /= 12;

        double u = 0;
        for (auto &__val : I[j]) u += __val.u * __val.u;
        u = std::sqrt(u) / 12;

        double ur = u / _I * 100;

        std::cout << std::format(
            "I  = {:.3f} ± {:.3f} A \t"
            "ur = {:.2f}% \n\n",
            _I, u, ur
        );
        
        

        std::cout << "--------------------\n";
    }

    return 0;
}