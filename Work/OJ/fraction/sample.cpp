// 下发测试程序
// 你可以自由修改这个文件，用于测试
// 对于未实现的接口，你可以暂时先注释掉
#include "frac.h"

signed main() {
    fraction <int> f;
    std::cout << f << std::endl; // 0/1

    f = 2;
    std::cout << f << std::endl; // 2/1

    f = { 2, -6 };
    std::cout << f << std::endl; // -1/3

    f = -~f;
    std::cout << f << std::endl; // 3/1

    f += f;
    std::cout << f << std::endl; // 6/1

    f *= f;
    std::cout << f << std::endl; // 36/1

    f /= ~f;
    std::cout << f << std::endl; // 1296/1

    f -= f;
    std::cout << f << std::endl; // 0/1
    std::cout << static_cast <double> (f) << std::endl; // 0

    if (f) {
        std::cout << "f is not zero" << std::endl;
    } else { // Output: "f is zero"
        std::cout << "f is zero" << std::endl;
    }

    try {
        f = f - ~f;
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl; // Divided by zero!
    }

    return 0;
}
