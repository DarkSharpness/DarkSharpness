/*
    Reference:
    https://github.com/CnTransGroup/EffectiveModernCppChinese/blob/master/src/8.Tweaks/item42.md
    省流: 别™乱用 emplace_back，这玩意甚至没有编译前检查
*/


#include <bits/stdc++.h>
// #include <Dark/inout>


signed main() {
    // 这会炸裂,因为是 explicit 构造函数
    // std::regex tmp = nullptr;
    /*
        std::regex tmp = std::regex(nullptr);  implicit nullptr_t -> const char*
        std::regex tmp{nullptr}; 同上

        这两个都会 gg
    */

    std::vector <std::regex> v;
    // v.emplace_back(nullptr); // 这个调用了 explicit 的构造哦~
    // 但事实上，这种调用会爆炸。

    std::vector <std::vector <int> > vec;

    vec.push_back({1,2,3}); /* 可以! */
    // vec.emplace_back({1,2,3}); /* 不可以! 编译器不知道 {} 内要转换成啥 */

    vec.emplace_back(std::vector <int> {4,5,6});    /* 行为完全同上 */
    vec.emplace_back <std::vector <int>> ({4,5,6}); /* 这是它的原型 */

    vec.emplace_back(std::initializer_list <int> {7,8,9}); /* 这个也行 */
    vec.emplace_back <std::initializer_list <int>> ({1,2,3}); /* 原型 */

    vec.emplace_back(1,2); /* 调用的是将一个元素赋值为 2 的构造函数，无法匹配初始化列表 */
    std::cout << vec.back().size() << '\n';

    std::vector <bool> vbool;
    vbool.push_back(true);

    std::cout << "Here awa\n";

    return 0;
}