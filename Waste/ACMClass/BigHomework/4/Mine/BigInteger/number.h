#ifndef _NUMBER_H_
#define _NUMBER_H_

#include <string>
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>


namespace sjtu {

struct complex {
    double real,imag;
    complex(double _r = 0,double _i = 0): real(_r),imag(_i) {}
    inline friend complex operator +(const complex &X,const complex &Y) {
        return complex(X.real + Y.real,X.imag + Y.imag);
    }
    inline friend complex operator -(const complex &X,const complex &Y) {
        return complex(X.real - Y.real,X.imag - Y.imag);
    }
    inline friend complex operator *(const complex &X,const complex &Y) {
        return complex(X.real * Y.real - X.imag * Y.imag, 
                       X.real * Y.imag + X.imag * Y.real);
    }
    inline friend complex operator *=(complex &X,const complex &Y) {
        return X = X * Y;
    }
    inline friend complex operator ~(const complex &X) {
        return complex(X.real,-X.imag);
    }
    inline void conjugate() {
        imag = -imag;
    }
    void setangle(double sita) {
        real = std::cos(sita);
        imag = std::sin(sita);
    }
};

constexpr double PI = 3.141592653589793238462643383;

class FFT_base {
  protected:
    
    constexpr static uint64_t lenb          = 4;   // log10(base)
    constexpr static uint64_t base          = 1e4; // base of FFT
    constexpr static uint64_t FFT_threshold = 00;  // FFT_threshold
    constexpr static uint64_t maxLen        = 20;  // maximum length for FFT
    constexpr static uint64_t initLen       = 6;   // initial length for vector
    static complex root[maxLen];
    constexpr static uint64_t unit[lenb] = {1,10,100,1000};

    // Functions part:

    inline static void reverse(complex *A,uint64_t *rev,uint32_t len);
    static void FFT(complex *A,uint32_t len,bool type);
    static inline void IFFT(complex *A,uint32_t len);
    FFT_base() = default;
    static inline void FFT_init();
};
complex FFT_base::root[FFT_base::maxLen]; // Initialize



/// @brief Easy Wrapping of vector.
class custom_vector : public std::vector <uint64_t> {
  public:
    /// @brief Copy the data of another data.
    /// @param vec The vector to copy from.
    inline void copy(const custom_vector &vec) {
        *this = vec;
    }
};


/**
 * @brief Custom integer type.
 * Maximum length is 
 * 
 */
class int2048 : private custom_vector,private FFT_base {
  private:
    static std::string buffer; // buffer inside
    int2048(uint64_t cap,bool flag);
    inline uint64_t operator ()(uint64_t idx)  const;


  public:
    // Sign of the number.
    // True if negative.False if positive.
    bool sign;

    friend int2048 add(const int2048 &X, const int2048 &Y) {
        return X + Y;
    }
    friend int2048 minus(const int2048 &X, const int2048 &Y) {
        return X - Y;
    }
    int2048 &add(const int2048 &Y) {
        return *this = *this + Y;
    }
    int2048 &minus(const int2048 &Y) {
        return *this = *this - Y;
    }


    friend int2048 operator +(const int2048 &X,const int2048 &Y);
    friend int2048 operator -(const int2048 &X,const int2048 &Y);
    friend int2048 operator *(const int2048 &X,const int2048 &Y);
    friend int2048 operator /(const int2048 &X,const int2048 &Y);
    friend int2048 operator %(const int2048 &X,const int2048 &Y);

    inline friend bool operator ==(const int2048 &X,const int2048 &Y);
    inline friend bool operator !=(const int2048 &X,const int2048 &Y);
    inline friend bool operator < (const int2048 &X,const int2048 &Y);
    inline friend bool operator <=(const int2048 &X,const int2048 &Y);
    inline friend bool operator > (const int2048 &X,const int2048 &Y);
    inline friend bool operator >=(const int2048 &X,const int2048 &Y);
    
    inline friend bool operator!(const int2048 &X);
    inline friend int2048 operator -(int2048 &&X);
    inline friend int2048 operator -(const int2048 &X);


    friend int2048& operator +=(int2048 &X,const int2048 &Y);
    friend int2048& operator -=(int2048 &X,const int2048 &Y);
    friend int2048& operator *=(int2048 &X,const int2048 &Y);
    friend int2048& operator /=(int2048 &X,const int2048 &Y);
    friend int2048& operator %=(int2048 &X,const int2048 &Y);


    friend int2048 Add(const int2048 &X,const int2048 &Y);
    friend int2048 Sub(const int2048 &X,const int2048 &Y);
    friend int2048 Mult_BF (const int2048 &X,const int2048 &Y);
    friend int2048 Mult_NTT(const int2048 &X,const int2048 &Y);
    friend int32_t Compare_abs(const int2048 &X,const int2048 &Y);
    // friend int2048 Inverse(const int2048 &X);
    void read(const std::string &str);
    void print(std::ostream &os) const;
    inline void reverse();
    friend int2048 operator <<(const int2048 &X,const uint64_t Y);
    friend int2048 operator >>(const int2048 &X,const uint64_t Y);

    friend std::istream &operator >>(std::istream &is,int2048 &dst);
    friend std::ostream &operator <<(std::ostream &os,const int2048 &src);

    int2048 &operator =(int2048 &&tmp);
    int2048 &operator =(const int2048 &tmp);

    explicit operator bool() const;
    explicit operator double() const;
    int2048(int2048 &&tmp);
    int2048(const int2048 &tmp);
    int2048(int64_t tmp);
    int2048(const std::string &str);
    ~int2048() = default;
    // ~int2048() {std::cout <<"Deallocate:"<<size()<<'\n';}
};
std::string int2048::buffer = ""; // Buffer for input and output.

const size_t SIZEOFINT2048 = sizeof(int2048);


}


#endif

