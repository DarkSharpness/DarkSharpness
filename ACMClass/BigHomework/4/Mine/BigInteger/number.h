#ifndef _NUMBER_H_
#define _NUMBER_H_

#include <complex>
#include <string>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>


namespace sjtu {


/**
 * @brief NTT related data.
 * You can't apply for an NTT_base object. 
 * 
 */
class NTT_base {
  protected:
    NTT_base() = default;
    uint64_t fastPow(uint64_t base,uint64_t pow,bool type) const;
    void NTT(uint64_t *A,uint32_t *rev,uint32_t len,uint32_t type) const;
    constexpr static uint64_t mod[2]  = {3892314113,3489660929}; // mod number
    constexpr static uint64_t lenb    = 18;   // base len in decimal
    constexpr static uint64_t base    = 1e18; // base of int2048 = 10 ^ lenb
    constexpr static uint64_t initLen = 2;    // initial length reserved
    constexpr static uint64_t rate    = 3;    // compressing rate
    constexpr static uint64_t NTTLen  = 1e6;  // pow(NTTLen,rate) = base
    constexpr static uint64_t BFLen   = 1e9;  // Brute Force length
    constexpr static uint64_t root[4] = {     // root and inv root
        3,3,(mod[0] + 1) / 3,(mod[1] + 1) / 3
    };  // common root
    constexpr static uint64_t unit[lenb] = { // units below base
        1,
        10,
        100,
        1000,
        10000,
        100000,
        1000000,
        10000000,
        100000000,
        1000000000,
        10000000000,
        100000000000,
        1000000000000,
        10000000000000,
        100000000000000,
        1000000000000000,
        10000000000000000,
        100000000000000000
    };
    /**
     * @brief Least length for NTT.
     * Note that 2 * threshold * base should be less than 2 ^ 64. 
     * 
     */
    constexpr static uint64_t NTT_threshold = 6; 
};

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
class int2048 : private custom_vector,private NTT_base {
  private:
    static std::string buffer; // buffer inside 
    int2048(uint64_t cap,bool flag);
    inline uint64_t operator ()(uint64_t idx) const;

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
    friend int2048 Mult_BF(const int2048 &X,const int2048 &Y);
    inline friend int32_t Compare_abs(const int2048 &X,const int2048 &Y);
    //inline void copy(const int2048 &tmp);
    void read(const std::string &str);
    void print(std::ostream &os) const;
    void move(std::vector <uint64_t> &tmp);
    void reverse();
    
    
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