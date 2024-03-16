#include <iostream>
#include <complex>

//�ڱ����ڼ䷵��һ�������С�ĳ���ֵ
//��Ϊ����ֻ��������Ĵ�С��
template<typename T, std::size_t N>                     //����
constexpr std::size_t arraySize(T (&)[N]) noexcept      //constexpr
{                                                       //��noexcept
    return N;                                           //����Ϣ
}                                                       //�뿴����

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