#include <bits/stdc++.h>

struct custom {
    int x;
    int y;
    friend auto operator <=>(const custom &lhs,const custom &rhs) = default;

    friend bool operator == (const custom &lhs,const custom &rhs) = default;
};

// std::strong_ordering ;


signed main() {
    custom x {0,1} , y {0,3};
    auto temp = x <=> y;
    auto tttt = temp.less;

    /**
     * @brief 第二个参数是 std::__cmp_cat::__unspec 类
     * 其构造函数只有传入一个自己类型的指针
     * 
     * 之所以可以和 0 比较，是因为 0 退化为了空指针 (void *)(0)
     * 不难发现，后面三个式子是等价的
     * 
     */
    const std::__cmp_cat::__unspec __agent(nullptr);
    std::cout << (tttt >    0   ) << '\n';
    std::cout << (tttt > nullptr) << '\n';
    std::cout << (tttt > __agent) << '\n';


    return 0;
}