#ifndef _NUMBER_H_
#define _NUMBER_H_
#define NUMBER_MODE 0 // 0 (Default) NTT || 1 FFT

#if NUMBER_MOD != 1

#include "vector.cc"
#include "complex.cc"

#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>




namespace sjtu {


class Number_base {
  protected:
    Number_base() = default;


    static constexpr uint64_t lenb = 5  ;
    static constexpr uint64_t base = 1e5;
    static constexpr uint64_t unit[lenb] = {
        1,10,100,1000,10000
    };

    // The minimum length for Newton Method division.
    static constexpr uint64_t DIV_minLen = 8;

    static inline void getRev (vector <size_t> &rev,size_t len);
    static inline void reverse(uint64_t *A,uint32_t *rev,size_t len);

};


/**
 * @brief NTT related data.
 * You can't apply for an NTT_base object. 
 * 
 */
class NTT_base : protected Number_base{
  protected:
    NTT_base() = default;
    
    // NTT mod numbers.
    constexpr static uint64_t mod[2] = {2281701377,3489660929};


    // The minimum length for NTT multiplication
    constexpr static uint64_t NTT_minLen = 8; 

    // The maximum 01bits for NTT multiplication 
    constexpr static uint64_t NTT_maxBit = 27;
    // The maximum length for NTT multiplication
    constexpr static uint64_t NTT_maxLen = 1 << NTT_maxBit;


    // Unit roots for NTT
    constexpr static uint64_t root[2][2][NTT_maxBit] = {
        //TODO
    };
    // Inverses for NTT
    constexpr static uint64_t inverse[2][NTT_maxBit] = {
        //TODO
    };


    template <bool NTT_type>
    static void quickPow(uint64_t base,uint64_t pow);
    template <bool NTT_type>
    static void NTT (uint64_t *A,size_t len,bool type);
    template <bool NTT_type>
    static void INTT(uint64_t *A,size_t len);


};



class FFT_base {
  protected:

    FFT_base() = default;

    // The maximum 01bits for NTT multiplication 
    constexpr static uint64_t FFT_maxBit = 27;
    // The maximum length for NTT multiplication
    constexpr static uint64_t FFT_maxLen = 1 << FFT_maxBit;


    static void FFT (complex *A,size_t len,bool type);
    static void IFFT(complex *A,size_t len);
};


/**
 * @brief Custom integer type.
 * 
 */
class int2048 : private vector <uint64_t>,NTT_base,FFT_base {
  private:
    static std::string buffer; // buffer inside
    int2048(uint64_t cap,bool flag);
    inline uint64_t operator ()(uint64_t idx)  const;
    friend int2048 operator ~(const int2048 &X);
    friend int32_t Abs_Compare(const int2048 &X,const int2048 &Y);
    friend int2048 Add(int2048 &X,const int2048 &Y,size_t len);
    friend int2048 Sub(int2048 &X,const int2048 &Y,size_t len);
    friend int2048 Mult_BF (const int2048 &X,const int2048 &Y);
    friend int2048 Mult_NTT(const int2048 &X,const int2048 &Y);

  public:
    // Sign of the number.
    // True if negative.False if positive.
    bool sign;
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

    friend int2048 operator <<(const int2048 &X,const uint64_t Y);
    friend int2048 operator >>(const int2048 &X,const uint64_t Y);

    
    void read(const std::string &str);
    void print(std::ostream &os) const;
    inline void reverse();
    
    
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
#endif