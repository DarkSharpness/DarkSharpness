#include <bits/stdc++.h>



/* Concept 等号右边本质是个 bool 变量 */

template <class T>
concept is_signed_integer   = std::is_signed_v   <T> && std::is_integral_v <T>;
template <class T>
concept is_unsigned_integer = std::is_unsigned_v <T> && std::is_integral_v <T>;


/* 
    最简单的方法就是在后面加上 requires 
    当然放在模板声明前后都一样 
*/

template <class T>
T lowbit(T __arg) noexcept
requires is_signed_integer <T> {
    return __arg & (-__arg);
}

template <class T>
requires is_unsigned_integer <T>
T sign_flag(T __arg) noexcept {
    return __arg >> ((sizeof(T) << 3) - 1);
}



/* 第二种写法就是直接把模板的 class 换成 concept 的约束 */

template <is_signed_integer T>
T min_integer_value =   T(1) << (sizeof(T) * 8 - 1) ;

template <class T>
requires is_signed_integer <T>
T max_integer_value = ~(T(1) << (sizeof(T) * 8 - 1));


template <is_signed_integer T>
bool is_min(T __arg) noexcept {
    return __arg == T(1) << (sizeof(T) * 8 - 1);
}

template <is_unsigned_integer T>
bool is_min(T __arg) noexcept {
    return __arg == 0;
}

/* 第三种是更加逆天的写法....... */

auto add(std::integral auto x,std::integral auto y) { return x + y; }


/* 
    值得一提的是，貌似 concept 变量不支持重载其他 requires.......
    当然，函数是没有一点问题的 qwq
*/

// template <is_unsigned_integer T>
// T min_integer_value =  T(0);

// template <class T>
// requires is_unsigned_integer <T>
// T max_integer_value = ~T(0);

template <class T>
bool is_max(T __arg) noexcept
requires is_signed_integer <T> {
    return ~__arg == (T(1) << (sizeof(T) * 8 - 1));
}

template <class T>
bool is_max(T __arg) noexcept
requires is_unsigned_integer <T> {
    return ~__arg == 0;
}

/*
    解决方案也很简单，使用正常的函数模板
    然后变量只是作为中转即可
    当然也可以类人智慧写法 :(
*/

/* 类人智慧写法 */
template <class T>
requires std::is_integral_v <T>
constexpr T integer_value_table[2] = { 0,T(1) << (sizeof(T) * 8 - 1)};

template <class T>
requires std::is_signed_v <T>
constexpr T get_integer_value() { return T(1) << (sizeof(T) * 8 - 1); }

template <class T>
requires std::is_unsigned_v <T>
constexpr T get_integer_value() { return 0; }

/*
    同样值得一提的是, requires 后面可以跟着不是 concept 的 bool constexpr
    但是 bool constexpr 不会被编译器检测，不会报错但是过不了编译
*/

template <class T>
requires std::is_integral_v <T>
constexpr T integer_value = 
    // integer_value_table <T> [std::is_signed_v <T>];
    get_integer_value <T> ();

/* Requires 还可以检测有没有这个属性 */

template <class T>
concept is_decrementable = requires (T t) { --t; };

/* 如果没有 iterator, 会直接返回 false 。所以注释掉内容的就不用了 */
template <class T>
concept has_decrement_iterator_type = 
    is_decrementable <typename T::iterator>;
// && requires {
//     typename T::iterator;
// } && ;

template <class T>
concept has_size_type = requires (T x) {
    {&x} -> std::convertible_to <void *>;
};


signed main() {
    std::cout << lowbit(10) << '\n';
    // std::cout << lowbit(114514u) << '\n';
    // std::cout << lowbit(0.1) << '\n';
    // std::cout << lowbit(std::vector <int> {1,2,3}) << '\n';

    std::cout << std::boolalpha;
    std::cout << is_min(0l) << '\n';
    std::cout << is_min(0u) << '\n';
    std::cout << is_max(0x7fffffff ) << '\n';
    std::cout << is_max(0x7fffffffu) << '\n';
    // std::cout << is_min(0.1) << '\n';
    // std::cout << is_max(0.2) << '\n';

    std::cout << integer_value <long>    << '\n';
    std::cout << add(1,2) << '\n';

    std::cout << has_decrement_iterator_type <int> << '\n'; 
    std::cout << has_decrement_iterator_type <std::unordered_set <int>> << '\n'; 
    std::cout << has_decrement_iterator_type <std::vector <int>> << '\n'; 

    std::cout << has_size_type <std::list <int>> << '\n';

    /* require concept 有报错 */
    // std::cout << min_integer_value <double> << '\n';

    /* require bool constant 无报错 */
    // std::cout << integer_value <double>  << '\n';

    return 0;
}