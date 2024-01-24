//
// Created by Administrator on 12/25/2023.
//

#ifndef UNTITLED1_FRACTION_H
#define UNTITLED1_FRACTION_H

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
class fraction {
private:
    _Tp up;
    _Tp down;
    static _Tp gcd(_Tp x, _Tp y) {
        while (y) {
            x %= y;
            std::swap(x, y);
        } return x;
    }

public:
    fraction() : up(), down(1) {}; // 默认构造函数, 构造为 0/0
    fraction(_Tp x) : up(x), down(1) {}; // 构造函数, 构造为 x/1
    fraction(_Tp x, _Tp y) {
        up = x;
        down = y;
        _Tp GCD = gcd(up, down);
        up /= GCD;
        down /= GCD;
    }

    fraction operator - () const {
        fraction<_Tp> ans = *this;
        ans.up = -ans.up;
        return ans;
    }
    fraction operator ~ () const {
        fraction<_Tp> ans = *this;
        if(ans.up == _Tp()) throw divided_by_zero(); // auto return after throw
        _Tp temp = ans.up;
        if(temp < _Tp()) {
            temp = - temp;
            ans.up = -ans.down;
        }
        else ans.up = ans.down;
        ans.down = temp;
        return ans;
    }

    fraction operator + (const fraction &r) const {
        fraction<_Tp> ans;
        ans.down = down * r.down;
        ans.up = up * r.down + r.up * down;
        _Tp GCD = gcd(ans.up, ans.down);
        ans.up /= GCD;
        ans.down /= GCD;
        return ans;
    }

    fraction operator - (const fraction &r) const {
        fraction<_Tp> ans;
        ans.down = down * r.down;
        ans.up = up * r.down - r.up * down;
        _Tp GCD = gcd(ans.up, ans.down);
        ans.up /= GCD;
        ans.down /= GCD;
        return ans;
    }

    fraction operator * (const fraction &r) const {
        fraction<_Tp> ans;
        ans.down = down * r.down;
        ans.up = up * r.up;
        _Tp GCD = gcd(ans.up, ans.down);
        ans.up /= GCD;
        ans.down /= GCD;
        return ans;
    }

    fraction operator / (const fraction &r) const {
        fraction ans;
        ans.down = down * r.up;
        ans.up = up * r.down;
        _Tp GCD = gcd(ans.up, ans.down);
        ans.up /= GCD;
        ans.down /= GCD;
        return ans;
    }   // 除法

    fraction &operator += (const fraction &rhs) {
        return *this = *this + rhs;
    }
    fraction &operator -= (const fraction &rhs) {
        return *this = *this - rhs;
    }
    fraction &operator *= (const fraction &rhs) {
        return *this = *this * rhs;
    }
    fraction &operator /= (const fraction &rhs) {
        return *this = *this / rhs;
    }

    explicit operator double()  const {
        return double(up) / double(down);
    }
    explicit operator bool()    const {
        if(up == _Tp()) return false;
        else return true;
    }

    friend bool operator == (const fraction &lhs, const fraction &rhs) {
        if(lhs.up == rhs.up && lhs.down == rhs.down) return true;
        else return false;
    }

    friend bool operator < (const fraction &lhs, const fraction &rhs) {
        if(lhs.up * rhs.down < rhs.up * lhs.down) return true;
        else return false;
    }

    friend std::ostream & operator << (std::ostream &os, const fraction &ob) {
        os << ob.up << '/' << ob.down;
        return os;
    }
};





#endif //UNTITLED1_FRACTION_H