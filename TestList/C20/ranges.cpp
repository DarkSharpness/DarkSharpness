#include <iostream>
#include <format>
#include <ranges>
#include <sstream>
#include <algorithm>
#include <array>

int sqr(int x) { return x * x; }
int add(int x) { return x + 1; }

signed main() {
    using _Func = decltype(sqr);
    _Func *arr[2] = {sqr, add};
    const std::array <int,3> a = {1, 2, 3};
    std::ranges::transform(
        a | std::views::transform(arr[0]) | std::views::transform(arr[1]),
        std::ostream_iterator<int>(std::cout, " "), [](int x) { return x; }
    );
    return 0;
}
