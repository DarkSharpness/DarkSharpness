#include <iostream>     // 输入输出
#include <stdexcept>    // 异常处理
// 你不可以使用任何其他的头文件!

struct divided_by_zero : std::exception {
    divided_by_zero()   = default;
    ~divided_by_zero()  = default;
    const char *what() const noexcept override { return "Divided by zero!"; };
};


// 请保留所有的接口声明，即使你没有实现它们。
// 否则可能出现编译错误，无法通过部分测试点。
template <typename _Tp>
struct fraction {
  public:
    // fraction();
    // fraction(_Tp);
    // fraction(_Tp, _Tp);

    // fraction(const fraction &)  = default;
    // fraction(fraction &&)       = default;
    // ~fraction()                 = default;

    // fraction &operator = (const fraction &)    = default;
    // fraction &operator = (fraction &&)         = default;

    // fraction operator - () const; // 取负数
    // fraction operator ~ () const; // 取倒数

    // fraction operator + (const fraction &) const;
    // fraction operator - (const fraction &) const;
    // fraction operator * (const fraction &) const;
    // fraction operator / (const fraction &) const;

    // fraction &operator += (const fraction &);
    // fraction &operator -= (const fraction &);
    // fraction &operator *= (const fraction &);
    // fraction &operator /= (const fraction &);

    // explicit operator double()  const;
    // explicit operator bool()    const;

    // friend bool operator == (const fraction &, const fraction &);
    // friend bool operator <  (const fraction &, const fraction &);

    // friend std::ostream & operator << (std::ostream &, const fraction &);
};
