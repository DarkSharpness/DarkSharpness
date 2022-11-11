#ifndef _NUMBER_H_
#define _NUMBER_H_

#include <string>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>


namespace sjtu {

class int2048 {
  private:
    std::vector <uint8_t> num;
    uint8_t& operator [](uint32_t idx);
    uint8_t  operator [](uint32_t idx) const;
    uint8_t  operator ()(uint32_t idx) const;
    uint32_t size() const;
    void push_back(uint8_t val);
    void resize(uint64_t siz);
    void reserve(uint64_t siz);
    void clear_zero();
    int2048(uint64_t cap,uint64_t siz);
  public:
    // Sign of the number.
    // True if negative.False if positive.
    bool sign;
 
    friend int2048 operator +(const int2048 &X,const int2048 &Y);
    friend int2048 operator -(const int2048 &X,const int2048 &Y);
    friend int2048 operator *(const int2048 &X,const int2048 &Y);
    friend int2048 operator /(const int2048 &X,const int2048 &Y);
    friend int2048 operator %(const int2048 &X,const int2048 &Y);
    friend int2048& operator -(int2048 &X);

    friend bool operator ==(const int2048 &X,const int2048 &Y);
    friend bool operator !=(const int2048 &X,const int2048 &Y);
    friend bool operator <(const int2048 &X,const int2048 &Y);
    friend bool operator <=(const int2048 &X,const int2048 &Y);
    friend bool operator >(const int2048 &X,const int2048 &Y);
    friend bool operator >=(const int2048 &X,const int2048 &Y);
    friend bool operator !(const int2048 &X);

    friend int2048& operator +=(int2048 &X,const int2048 &Y);
    friend int2048& operator -=(int2048 &X,const int2048 &Y);
    friend int2048& operator *=(int2048 &X,const int2048 &Y);
    friend int2048& operator /=(int2048 &X,const int2048 &Y);
    friend int2048& operator %=(int2048 &X,const int2048 &Y);

    friend int2048 Add(const int2048 &X,const int2048 &Y);
    friend int2048 Sub(const int2048 &X,const int2048 &Y);
    friend int32_t Compare_abs(const int2048 &X,const int2048 &Y);
    void zero();


    friend std::istream &operator >>(std::istream &is,int2048 &dst);
    friend std::ostream &operator <<(std::ostream &os,const int2048 &src);

    int2048 &operator =(int2048 &&tmp) = default;
    int2048 &operator =(const int2048 &tmp) = default;
    explicit operator bool() const;
    explicit operator double() const;


    int2048();
    int2048(int2048 &&tmp);
    int2048(long long tmp);
    int2048(const std::string &str);

    //~int2048() = default;
    ~int2048() {
        std::cout << "Deconstruct:" << num.size() << '\n';
    }


};

constexpr uint64_t fastPow(uint64_t base,uint32_t pow);

}


#endif