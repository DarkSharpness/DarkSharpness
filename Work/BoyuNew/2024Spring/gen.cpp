#include <thread>
#include <vector>
#include <format>
#include <iostream>
#include <filesystem>

struct checker {
    std::string msg;        // Error message.
    const bool kill = true; // Whether to kill on failure.
    int fails = 0;          // Count of failures.

    checker &operator()(auto &&cond) {
        if (cond) return *this;
        ++fails;
        if (kill) {
            std::cerr << std::format("\033[31m[Error]: {}\033[0m\n", msg);
            std::exit(1);
        } else {
            std::cerr << std::format("\033[33m[Warning]: {}\033[0m\n", msg);
            return *this;
        }
    }

    checker &on_success(std::string_view msg) {
        if (!fails) std::cerr << msg;
        return *this;
    }

    checker &on_failure(std::string_view msg) {
        if (fails) std::cerr << msg;
        return *this;
    }

    checker & reset() { fails = 0; return *this; }
};

std::string path; // Relative path to the folder

void compile_std() {
    std::string __cmd = // Compile std.cpp
        std::format("g++ -std=c++17 -O2 {0}/std.cpp -o std", path);

    checker("Fail to compile std.cpp!")(std::system(__cmd.c_str()) == 0);
}

void clean_up() {
    std::filesystem::remove("std.exe");
    std::filesystem::remove(std::format("{}/std.exe", path));
    std::filesystem::remove(std::format("{}/data/generator.exe", path));
}

void generate(int i) {
    std::string __cmd = std::format(
        "std.exe < {0}/data/{1}.in > {0}/data/{1}.out", path, i);

    checker(std::format("Fail to generate data {}!", i), false)
        (std::system(__cmd.c_str()) == 0)
            .on_success(std::format("Data {} generated!\n", i));
}

signed main() {
    std::cout << "Enter the number of the folder: ";
    size_t num, prob;

    checker("Invalid input!")(std::cin >> num);

    std::cout << "Enter the number of the problem: ";
    checker("Invalid input!")(std::cin >> prob);

    path = std::format("L{}/T{}", num, prob);
    checker("No such folder!")(std::filesystem::exists(path));

    compile_std();

    size_t cnt = 1;
    std::vector <std::thread> threads;
    while (true) {
        auto file = std::format("{}/data/{}.in", path, cnt);
        if (!std::filesystem::exists(file)) break;
        threads.emplace_back(generate, cnt++);
    }

    for (auto &thread : threads) thread.join();
    clean_up();

    std::cerr << "All done!\n";
    return 0;
}
