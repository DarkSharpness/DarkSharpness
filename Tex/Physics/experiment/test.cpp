#include <iostream>
#include <format>
#include <vector>
#include <cmath>


constexpr double t[] = {
    30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0,
    73.0, 73.6, 74.0, 74.5, 75.0, 75.3, 75.6, 75.8, 76.3,
    76.8, 77.0, 77.5, 78.0, 78.4, 78.7, 79.0, 79.3, 79.8,
    80.2, 80.5, 81.0, 81.5, 82.0, 82.5, 82.7, 82.9, 83.3,
    83.8, 84.4, 84.6, 85.0, 85.3, 85.7, 86.0, 86.5, 87.5
};

constexpr double U[] = {
    23.095,23.065,23.021,22.977,22.930,22.891,22.859,22.840,22.810,
    22.017,21.709,21.389,21.007,20.555,20.279,19.973,19.720,19.220,
    18.718,18.450,17.960,17.362,16.763,16.360,16.028,15.693,14.967,
    14.500,14.107,13.362,12.633,12.100,11.470,11.059,10.799,10.317,
    9.833 , 9.127, 8.666, 8.020, 7.720, 7.471, 7.130, 6.736, 6.138
};

struct unit {
    double t;
    double U;
};

signed main() {
    constexpr size_t length = sizeof(U) / sizeof(U[0]);
    std::vector <unit> data;
    data.reserve(length);
    for(size_t i = 0 ; i != length ; ++i) data.emplace_back(t[i], U[i]);
    data.erase(data.begin() + 36);
    data.erase(data.begin() + 33);
    data.erase(data.begin() + 35);
    data.erase(data.begin() + 20);
    freopen("data1.txt", "w", stdout);
    for(auto pair : data) {
        std::cout << std::format("{:.3}\t{:.5}\n", pair.t, pair.U);
    }
    freopen("data2.txt", "w", stdout);
    unit last = {std::nan(""), std::nan("")};
    std::cout << '\n';
    for(auto pair : data) {
        if (!std::isnan(last.t)) {
            std::cout << std::format("{:.6}\n", (pair.U - last.U) / (pair.t - last.t));
        }
        last = pair;
    }

    return 0;
}