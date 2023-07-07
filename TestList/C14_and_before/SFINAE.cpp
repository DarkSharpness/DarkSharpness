/*
    Reference:
    https://en.cppreference.com/w/cpp/language/overload_resolution

*/

#include <bits/stdc++.h>
// #include <Dark/inout>


/**
 * @brief SFINAE: Substitution Failure Is Not An Error!
 * C++ 模板元编程基础。对于模板中不确定的参数(依赖其他传入的模板参数的参数)，
 * 如果出错了不会直接报错，而是会尝试匹配其他的模板
 * 
 */

template <class T = int,std::enable_if_t <std::is_same <T,int>::value,long> = 0>
int get_custom_value() { return 1919810; }

template <class T = double,std::enable_if_t <std::is_same <T,long>::value,int> = 0>
int get_custom_value() { return 114514;  }

struct X { using typeA = int; };
struct Y { using typeB = int; };
struct Z { using typeA = Z;  };

template <class T> void foo(typename T::typeA) { std::cout << "A type\n"; }
template <class T> void foo(typename T::typeB) { std::cout << "B type\n"; }
template <class T> void foo(T)                 { std::cout << "O type\n";  }


/* 重复的匹配会带来错误,只能有且只有一个匹配! 例如下面注释的代码 */

// template <class T,size_t x = 0>
// int get_custom_value() { return 2333333;  }


/**
 * @brief 特别需要注意的是，模板变量貌似不支持 SFINAE
 * 
 */

// template <class T,std::enable_if_t <std::is_same <T,int>::value,long> = 0>
// int custom_value = 1919810;

/**
 * @brief 特别需要注意的是，模板变量貌似不支持 SFINAE
 * 
 */
// template <class T,std::enable_if_t <!std::is_same <T,int>::value,long> = 0>
// int custom_value = 114514;

/**
 * @brief 一般会用 is_xxx_v 来解决这个问题 (in C++ 17)
 * 
 */
template <class T>
int custom_value = get_custom_value <T> ();

/**
 * @brief 当然，SFINAE 不止以上这个版本
 * 可以把 enable_if_t 的部分写在函数参数/返回参数/模板参数 里面
 * 但是 SFINAE 不会检查函数内部的东西,这就注定了 static_assert 不兼容
 * 
 */


template <class T>
void func(std::enable_if_t <std::is_same<int32_t,T>::value,void>* = nullptr) {
    std::cout << "This is a 32-bit signed integer!\n";
}

template <class T>
void func(std::enable_if_t <std::is_same<int64_t,T>::value,void>* = nullptr) {
    std::cout << "This is a 64-bit signed integer!\n";
} 

template <class T>
auto test() -> std::enable_if_t <std::is_same<int32_t,T>::value,void> {
    std::cout << "This is a 32-bit signed integer!\n";
}

template <class T>
auto test() -> std::enable_if_t <std::is_same<int64_t,T>::value,void> {
    std::cout << "This is a 32-bit signed integer!\n";
}

/**
 * @brief 指的一提的是, SFINAE 和 static_assert 都会不会产生运行开销，
 * 但是 SFINAE 可以在编译时候确定重载哪个函数，从而完成函数选择。
 * 而 static_assert 会在第一个匹配的函数那里报错，不会尝试其他的重载。
 * 所以，不要在 SFINAE 里面乱用 static_assert!!!
 * 
 */


auto main() -> signed {
    /* 匹配的模板是 get_custom_value <long,1(int)> */
    std::cout << custom_value <long> << '\n';
    /* 匹配的模板是 get_custom_value <int,0(long)> */
    std::cout << custom_value <int>  << '\n';
    /* 有默认参数也不是不可以......甚至默认参数可以不一样 */
    std::cout << get_custom_value() << '\n';

    func <int32_t> ();
    func <int64_t> ();
    test <int32_t> ();
    test <int64_t> ();

    /* 下面是对于三个 foo 的匹配情况 */

    /* Success Failure Failure */
    foo <X> (1);
    /* Failure Success Failure */
    foo <Y> (1);
    /* Success Failure Sucsess 由于多匹配，所以飞了......  */
    // foo <Z> (1);
    /* Failure Failure Success */
    foo <int> (4);

    return 0;
}