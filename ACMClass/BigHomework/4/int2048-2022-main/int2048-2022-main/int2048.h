#ifndef SJTU_BIGINTEGER
#define SJTU_BIGINTEGER


#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>


namespace sjtu {
class int2048 {
  // todo
public:
  // 构造函数
  int2048();
  int2048(long long x);
  int2048(const std::string &s);
  int2048(const int2048 &);



  // 读入一个大整数
  void read(const std::string &s);
  // 输出储存的大整数
  void print();

  // 加上一个大整数
  int2048 &add(const int2048 &);
  // 输出两个大整数之和
  friend int2048 add(int2048, const int2048 &);

  // 减去一个大整数
  int2048 &minus(const int2048 &);
  // 输出两个大整数之差
  friend int2048 minus(int2048, const int2048 &);

  // ===================================
  // Integer2
  // ===================================

  int2048 &operator=(const int2048 &);

  int2048 &operator+=(int2048);
  friend int2048 operator+(int2048, const int2048 &);

  int2048 &operator-=(int2048);
  friend int2048 operator-(int2048, const int2048 &);

  int2048 &operator*=(const int2048 &);
  friend int2048 operator*(int2048, const int2048 &);

  int2048 &operator/=(const int2048 &);
  friend int2048 operator/(int2048, const int2048 &);

  friend std::istream &operator>>(std::istream &, int2048 &);
  friend std::ostream &operator<<(std::ostream &, const int2048 &);
 
  inline friend bool operator==(const int2048 &, const int2048 &);
  inline friend bool operator!=(const int2048 &, const int2048 &);
  inline friend bool operator< (const int2048 &, const int2048 &);
  inline friend bool operator> (const int2048 &, const int2048 &);
  inline friend bool operator<=(const int2048 &, const int2048 &);
  inline friend bool operator>=(const int2048 &, const int2048 &);
};
} // namespace sjtu

#endif
