#include <fstream>
#include <iomanip>
#include <iostream>

auto extract_integer(std::string_view str) {
    while (!std::isdigit(str.front()))
        str.remove_prefix(1);
    while (!std::isdigit(str.back()))
        str.remove_suffix(1);
    return std::stoull(std::string(str));
}

constexpr double kMIN = 0.75;
constexpr double kMAX = 1.10;

constexpr double kUnacceptable  = 0.2;
constexpr double kImpossible    = 2.0;

signed main(int argc, char* argv[]) {
    std::ifstream input (argv[1]);
    std::ifstream output(argv[2]);
    std::ifstream answer(argv[3]);
    std::ofstream score(argv[4]);
    std::ofstream message(argv[5]);
    std::string str, tmp;

    double final_score = 1.0;

    try {
        std::getline(answer, str);
        if (!str.starts_with("Benchmark")) {
            do {
                const auto n = std::stoull(str);
                if (!std::getline(output, str))
                    throw std::runtime_error("Wrong Answer");
                const auto m = std::stoull(str);
                if (n != m) throw std::runtime_error("Wrong Answer");
            } while (std::getline(answer, str));
        } else {
            if (!std::getline(output, str) || !std::getline(output, tmp))
                throw std::runtime_error("Wrong Answer");

            message << str << '\n' << tmp << '\n';

            // str: your map time ...
            // tmp: std::map time ...

            const double custom_time = extract_integer(str) ? : 1;
            const double stdmap_time = extract_integer(tmp) ? : 1;

            const double ratio = stdmap_time / custom_time;
            message << std::fixed << std::setprecision(2);

            if (ratio < kMIN) {
                message << "Your map is "
                        << ratio * 100
                        << "% the speed of std::map. 😇 (-"
                        << (1 / ratio - 1) * 100
                        << "%)\n";
            } else if (ratio > kMAX) {
                message << "Your map is "
                        << ratio * 100
                        << "% the speed of std::map. 😊 (+"
                        << (ratio - 1) * 100
                        << "%)\n";
            } else {
                message << "Your map is about as fast as std::map.\n";
            }

            if (ratio < kUnacceptable) {
                message << "思考一下哪里还能再优化一下吧！😘\n";
            } else if (ratio > kImpossible) {
                message << "这个成绩有点离谱了，你确定你没有作弊吗？🤔\n";
            }
        }
    } catch (const std::exception &e) {
        score << std::setprecision(2) << 0.0;
        message << e.what();
        return 0;
    } catch (...) {
        score << std::setprecision(2) << 0.0;
        message << "Unknown error...";
        return 0;
    }
    score << std::setprecision(2) << final_score;
    return 0;
}
