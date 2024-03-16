#include <iostream>
#include <complex>

//在编译期间返回一个数组大小的常量值
//因为我们只关心数组的大小）
template<typename T, std::size_t N>                     //关于
constexpr std::size_t arraySize(T (&)[N]) noexcept      //constexpr
{                                                       //和noexcept
    return N;                                           //的信息
}                                                       //请看下面

int a[100];
int b[2 * arraySize(a)];

template<typename T>
void func(T *) {}

signed main() {
    const int x = 1;
    func(&x);
    decltype (auto) b = x;
    std::complex <double> c,d;
    c + d = d;

    return 0;
}