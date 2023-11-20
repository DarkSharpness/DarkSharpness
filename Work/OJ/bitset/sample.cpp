#include "ans.h" // 你的实现文件路径

void print(dynamic_bitset &dyn) {
    std::cout << "Size: " << dyn.size() << " | ";
    for (std::size_t i = 0 ; i != dyn.size() ; ++i) std::cout << dyn[i];
    std::cout << '\n';
}

signed main() {
    std::string str = "01";
    for (int i = 0 ; i < 6 ; ++i) str += str;
    dynamic_bitset dyn {str};
    print(dyn);
    return 0;
}
