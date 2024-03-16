#include <bits/stdc++.h>
// #include <Dark/inout>

struct testA { using typeA = int; };
struct testB { using typeB = int; };

/*
    这些当然可以 SFINAE 解决
*/

template <class T>
typename T::typeA func() {
    typename T::typeA y = 114514;
    return y;
}

template <class T>
typename T::typeB func() {
    typename T::typeB y = 1919810;
    return y;
}

/* 如果这样，参数类型错误编译后才会报错 */
template <class T,class ...Args>
T & ass(T &obj,Args &&...args) {
    return obj = T(std::forward <Args> (args)...) ;
}

/* 如果这样，参数类型错误编译前就会报错 */
template <class T,class ...Args>
requires std::is_constructible_v <T,Args...>
T &better_ass(T &obj,Args &&...args) {
    return obj = T(std::forward <Args> (args)...) ;
}



struct custom {
    int x{2};
    int y{3};
    custom() noexcept = default;
    custom(int __x,int __y = 0) noexcept : x(__x),y(__y) {}
    explicit operator long long() { return (long long)x << 32 | y; }
};


signed main() {
    std::cout << std::boolalpha;
    std::cout << func <testA> () << '\n';

    std::vector <custom> v;
    std::cout 
        << std::is_constructible_v <custom,int *>   << ' '
        << std::is_constructible_v <custom,int,int> << ' '
        << std::is_constructible_v <custom,int>     << ' '
        << std::is_constructible_v <custom>         << '\n';
    
    custom __cst;
    
    // 模板内部出错，只有在编译后才会报错! 而且超级长
    // v.emplace_back(nullptr);
    // ass(__cst,1,4,5);

    // 解决方案 1: SFINAE: 可以放在 函数参数/返回参数(不一定全都适用),模板参数
    //          在本例中，模板参数，返回参数，函数参数均不可继续添加，直接 gg!
    // 解决方案 2: concept! requires!

    // 会报错 
    // better_ass(__cst,1,4,5);
    // better_ass(__cst,nullptr);

    // std::is_convertible_v 

    better_ass(__cst,1,4);
    std::cout << __cst.x << ' ' << __cst.y << '\n';

    std::cout 
        << std::is_convertible_v <int,double> << ' '
        << std::is_convertible_v <double,int> << '\n';

    return 0;
}