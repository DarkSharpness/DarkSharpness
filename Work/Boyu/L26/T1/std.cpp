/// @author DarkSharpness
/// 大家好，这里是 Dark 教授
/// 前段时间有点事情出差了
/// 最近发现抄袭题解的人特别多
/// 我可以理解大家，毕竟我也是这么过来的
/// 如果实在不会，确实可以看看题解找找灵感
/// 但是希望大家不要仅仅做题解的搬运工
/// 你要理解题解为什么是这么做的
/// 学习是为了自己，不是为了 OJ 上的 AC
/// 总之，希望各位不要给未来的自己留下遗憾
/// 以上.
/// 如有不会欢迎提问!

#include <iostream>
#include <algorithm>

const int N = 1 << 17;
int x[N];

signed main() {
    // 这个是用来加速 cin cout
    // 需要注意使用这个以后，不能再用 scanf/printf 等等
    // 只能用 cin cout 输出!!!
    std::ios::sync_with_stdio(false);

    // 输入部分
    int n,k;
    std::cin >> n >> k;
    for(int i = 0 ; i < n ; ++i)
        std::cin >> x[i];

    // 处理部分
    // 注意到归并完 k 轮后，其实就是每个 2 的 k 次方段拍好序
    // 所以直接分段 sort 即可
    const int m = 1 << k;
    for(int i = 0 ; i < (n >> k) ; ++i)
        std::sort(x + i * m,x + i * m + m);

    // 输出部分
    for(int i = 0 ; i < n ; ++i)
        std::cout << x[i] << ' ';
    return 0;
}
