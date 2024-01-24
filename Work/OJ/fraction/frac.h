#include <iostream>     // 输入输出
#include <stdexcept>    // 异常处理
// 你不可以使用任何其他的头文件!


// 下发异常类。你不需要修改这个类。
struct divided_by_zero final : std::exception {
public:
    divided_by_zero()   = default;
    ~divided_by_zero()  = default;
    const char *what() const noexcept override { return "Divided by zero!"; };
};


// 请保留所有的接口声明，即使你没有实现它们。
// 否则可能出现编译错误，无法通过部分测试点。
template <typename _Tp>
struct fraction {
public:
    fraction();             // 默认构造函数, 构造为 0/1
    fraction(_Tp x);        // 构造函数, 构造为 x/1
    fraction(_Tp x, _Tp y); // 构造函数, 构造为 x/y

    fraction operator - () const; // 返回负数
    fraction operator ~ () const; // 返回倒数

    fraction operator + (const fraction &) const;   // 加法
    fraction operator - (const fraction &) const;   // 减法
    fraction operator * (const fraction &) const;   // 乘法
    fraction operator / (const fraction &) const;   // 除法

    fraction &operator += (const fraction &rhs);
    fraction &operator -= (const fraction &rhs);
    fraction &operator *= (const fraction &rhs);
    fraction &operator /= (const fraction &rhs);

    explicit operator double()  const;  // 转换为 double
    explicit operator bool()    const;  // 转换为 bool

    friend bool operator == (const fraction &, const fraction &);   // 判断相等
    friend bool operator <  (const fraction &, const fraction &);   // 判断小于

    friend std::ostream & operator << (std::ostream &, const fraction &);   // 输出
};
