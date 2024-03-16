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

    static inline uint64_t fastPow0(uint64_t base,uint64_t pow);
    static inline uint64_t fastPow1(uint64_t base,uint64_t pow);
    static void NTT0(uint64_t *A,uint32_t len,bool type);
    static void NTT1(uint64_t *A,uint32_t len,bool type);
    static inline void reverse(uint64_t *A,uint32_t *rev,uint32_t len);
    static inline void getRev(std::vector <uint32_t> &rev,uint32_t len);
    static inline uint64_t getMult(uint64_t A0,uint64_t A1,uint64_t inv);


    constexpr static uint64_t NTT_threshold = 12; // where NTT start from(>=0)
    constexpr static uint64_t DIV_threshold = 10; // where DIV start from(>=5)


    constexpr static uint64_t mod[2]  = {2281701377,3489660929}; // mod number
    constexpr static uint64_t lenb    = 6;   // base len in decimal
    constexpr static uint64_t base    = 1e6; // base of int2048 = 10 ^ lenb
    constexpr static uint64_t initLen = 4;   // initial length reserved
    constexpr static uint64_t NTTLen  = 22;  // Max NTT capable length
    constexpr static uint64_t MaxLen  = 1 << NTTLen; // Maximum possible NTT length
    constexpr static uint64_t unit[lenb] = { // units below base
        1,
        10,
        100,
        1000,
        10000,
        100000,
        // 1000000,
    };

    constexpr static uint64_t root[2][2][NTTLen]= {  // unit roots
        2281701376,344250126,483803410,617790083,2023592065,
        216937880,123697435,1639385633,1301610063,865646229,
        1780348903,799681555,977546242,1286750706,1294996786,
        2270548020,451618310,637539285,231852688,1783582410,
        1346120317,1057547068,

        2281701376,1937451251,582229479,1778233327,996068929,
        533126167,1540362740,1845123106,1922965124,1184734049,
        369448383,1732276489,1444283332,92283190,2059450554,
        114788634,1156211696,2033086166,1274602630,1845241368,
        656109765,1987373021,

        3489660928,1841841630,1054308003,1513900834,1424003439,
        3290428437,2792923286,424291397,1938306374,731827882,
        340708175,1005229295,3231347667,962117947,1030533309,
        725028937,3369885469,72934420,758575992,3373763992,
        1882435536,1143890192,

        3489660928,1647819299,1761617041,724177331,38202934,
        2302762011,917171561,3348395406,763600137,382076615,
        417640332,3318291862,2451874772,3398023446,1583677827,
        997063351,2673837393,2327172879,845347823,1749721614,
        2180195085,87513231,
    };

    constexpr static uint64_t inverse[2][NTTLen] = { // inverses
        1,1140850689,1711276033,1996488705,2139095041,2210398209,
        2246049793,2263875585,2272788481,2277244929,2279473153,
        2280587265,2281144321,2281422849,2281562113,2281631745,
        2281666561,2281683969,2281692673,2281697025,2281699201,
        2281700289,

        1,1744830465,2617245697,3053453313,3271557121,3380609025,
        3435134977,3462397953,3476029441,3482845185,3486253057,
        3487956993,3488808961,3489234945,3489447937,3489554433,
        3489607681,3489634305,3489647617,3489654273,3489657601,
        3489659265,
    };
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
 * 
 */
class int2048 : private custom_vector,private NTT_base {
  private:
    static std::string buffer; // buffer inside
    int2048(uint64_t cap,bool flag);
    inline uint64_t operator ()(uint64_t idx)  const;
    friend int2048 operator ~(const int2048 &X);
    friend int2048 &selfAdd(int2048 &X);
    friend int2048 &selfSub(int2048 &X);

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

    friend int2048 operator <<(const int2048 &X,const uint64_t Y);
    friend int2048 operator >>(const int2048 &X,const uint64_t Y);

    friend int2048 Add(const int2048 &X,const int2048 &Y);
    friend int2048 Sub(const int2048 &X,const int2048 &Y);
    friend int2048 Mult_BF (const int2048 &X,const int2048 &Y);
    friend int2048 Mult_NTT(const int2048 &X,const int2048 &Y);
    friend int2048 Div_BF(const int2048 &X,const int2048 &Y);
    friend int2048 Div_NT(const int2048 &X,const int2048 &Y);
    friend int32_t Compare_abs(const int2048 &X,const int2048 &Y);

    int2048 Sub_abs_at(const int2048 &Y,uint64_t len);
    int32_t Compare_abs_at(const int2048 &Y,uint64_t len) const;

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
