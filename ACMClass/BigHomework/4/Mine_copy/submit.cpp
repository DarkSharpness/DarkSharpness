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
    constexpr uint64_t fastPow(uint64_t base,uint64_t pow,uint32_t type);
    constexpr static uint64_t modA    = 3892314113; // mod number A
    constexpr static uint64_t modB    = 3489660929; // mod number B
    constexpr static uint64_t lenb    = 18;   // base len in decimal
    constexpr static uint64_t base    = 1e18; // base of int2048
    constexpr static uint64_t initLen = 2;    // initial length reserved
    constexpr static uint64_t rate    = 3;    // compressing rate
    constexpr static uint64_t NTTLen  = 1e6;  // pow(NTTLen,rate) = base.
    constexpr static uint64_t root[3] = {3};  // common root
    constexpr static uint64_t unit[lenb * rate] = { // units below base
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
    inline friend int32_t Compare_abs(const int2048 &X,const int2048 &Y);
    //inline void copy(const int2048 &tmp);
    void read(const std::string &str);
    void print(std::ostream &os) const;
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

#ifndef _NUMBER_CC_
#define _NUMBER_CC_
#include "number.h"


/**
 * @brief This part includes basic functions for int2048.
 * 
 */
namespace sjtu {
/** 
 * @brief Safe const reference to idx.
 * @return 0 if idx >= size() || element at idx otherwise 
*/
inline uint64_t int2048::operator ()(uint64_t idx) const {
    return idx >= size() ? 0 : (*this)[idx];
}

/**
 * @brief Reverse a number's sign. \n 
 * Use it instead of * (-1) or x = -x.
 * 
*/
void int2048::reverse() {
    sign = !sign;
}

/**
 * @brief Judge whether abs(X) > abs(Y) in O(log(X*Y)) time.\n 
 * Naturally,it satisfies that Compare_abs(X,Y) = -Compare_abs(Y,X).
 * 
 * @return 1  if abs(X) > abs(Y) ||
 *         0  if abs(X) = abs(Y) ||
 *         -1 if abs(X) < abs(Y) ||
 */
inline int32_t Compare_abs(const int2048 &X,const int2048 &Y) {
    if(X.size() != Y.size()) {
        return X.size() > Y.size() ? 1 : -1;
    }
    for(uint64_t i = X.size() - 1 ; i != -1ULL ; --i) {
        if(X[i] != Y[i]) {
            return X[i] > Y[i] ? 1 : -1; 
        }
    }
    return 0;
}

/**
 * @brief Initialize from a string.
 * 
 * @param str The string to initialize from.
 */
void int2048::read(const std::string &str) {
    if(str.front() == '-') sign = true;
    else                   sign = false;
    clear(); // clear the previous data.
    if(str.size() == sign + 1u && str.back() == '0') { // 0 case
        sign = false;
        push_back(0);
        return;
    }
    reserve(1 + (str.size() - sign) / lenb);
    uint64_t i    = str.size();
    uint64_t cnt  = 0;
    uint64_t ret  = 0;
    while(i-- != sign) { // Loop in [sign,str.size())
        ret += unit[cnt] * (str[i] ^ '0');
        if(++cnt == lenb) {
            push_back(ret);
            ret = cnt = 0;
        } else {
        }
    }
    if(cnt) {
        push_back(ret);
    }
}

/** 
 * @brief Print out the inside number.
 * Default outstream is std::cout.
 * 
*/ 
void int2048::print(std::ostream &os = std::cout) const{
    if(sign) os << '-';
    os << back();
    buffer.resize((size() - 1) * lenb);
    //static char c[lenb+1]; // char string for printing.
    for(uint64_t i = 0 ; i < size() - 1 ; ++i) {
        uint64_t ret = (*this)[size() - 2 - i];
        for(uint64_t j = lenb - 1 ; j != -1ULL ; --j) {
            buffer[i * lenb + j] = (ret % 10) ^ '0';
            ret /= 10;
        }
    }
    os << buffer;
}

/**
 * @brief Add X by Y in X's sign.
 * 
 * @return int2048 sgn(X) * (abs(X) + abs(Y)).
 */
int2048 Add(const int2048 &X,const int2048 &Y) {
    uint64_t len = std::max(X.size(),Y.size());
    int2048 ans(len + 1u,X.sign);
    uint64_t ret = 0;
    for(uint64_t i = 0; i < len ; ++i) {
        ret += X(i) + Y(i);
        if(ret < int2048::base) {
            ans.push_back(ret);
            ret = 0;
        } else { // Addition overflow.
            ans.push_back(ret - int2048::base);
            ret = 1;
        }
    }
    if(ret) ans.push_back(1);
    return ans;
}

/**
 * @brief Subtract X by Y in X's sign.
 * Make sure abs(X) > abs(Y).
 * 
 * @return int2048 sgn(X) * (abs(X) - abs(Y)).
 */
int2048 Sub(const int2048 &X,const int2048 &Y) {
    int2048 ans(X.size(),X.sign);
    uint64_t ret = 0;
    for(uint64_t i = 0 ; i < X.size() ; ++i) {
        ret += X[i] - Y(i);
        if(ret < int2048::base) {
            ans.push_back(ret);
            ret = 0;
        } else { // Subtraction overflow.
            ans.push_back(ret + int2048::base);
            ret = -1ULL;
        }
    }
    while(!ans.back()) ans.pop_back();
    return ans;
}

}

/**
 * @brief This part includes logical operators for int2048.
 * 
 */
namespace sjtu {

/// @return bool true if X == Y 
inline bool operator ==(const int2048 &X,const int2048 &Y) {
    if(X.sign != Y.sign || X.size() != Y.size()) {
        return false;
    }
    for(uint64_t i = 0 ; i != X.size() ; ++i) {
        if(X[i] != Y[i]) return false;
    }
    return true;
}

/// @return bool true if X != Y
inline bool operator !=(const int2048 &X,const int2048 &Y) {
    if(X.sign != Y.sign || X.size() != Y.size()) {
        return true;
    }
    for(uint64_t i = 0 ; i != X.size() ; ++i) {
        if(X[i] != Y[i]) return true;
    }
    return false;
}

/// @return bool true if X < Y 
inline bool operator <(const int2048 &X,const int2048 &Y) {
    if(X.sign != Y.sign) return X.sign > Y.sign;
    return (X.sign ? Compare_abs(Y,X) : Compare_abs(X,Y)) < 0;
}

/// @return bool true if X <= Y 
inline bool operator <=(const int2048 &X,const int2048 &Y) {
    if(X.sign != Y.sign) return X.sign > Y.sign;
    return (X.sign ? Compare_abs(Y,X) : Compare_abs(X,Y)) <= 0;
}

/// @return bool true if X > Y 
inline bool operator >(const int2048 &X,const int2048 &Y) {
    if(X.sign != Y.sign) return X.sign < Y.sign;
    return (X.sign ? Compare_abs(Y,X) : Compare_abs(X,Y)) > 0;
}

/// @return bool true if X >= Y 
inline bool operator >=(const int2048 &X,const int2048 &Y) {
    if(X.sign != Y.sign) return X.sign < Y.sign;
    return (X.sign ? Compare_abs(Y,X) : Compare_abs(X,Y)) >= 0;
}

/// @return bool true if X != 0 
inline bool operator !(const int2048 &X) { 
    return X.back();
}

}


/**
 * @brief This part includes arithmetic operators for int2048.
 * 
 */
namespace sjtu {

/**
 * @brief Return the number of  X * (-1).
 * 
 * @return int2048 -X
 */
int2048 operator -(int2048 &&X) {
    int2048 ans(0,!X.sign);
    ans.swap(X);
    return ans;
}


/**
 * @brief Return the number of X * (-1).
 * If you simply want to multiply X by -1,
 * please use reverse() instead.
 * 
 * @return int2048 -X
 */
int2048 operator -(const int2048 &X) {
    int2048 ans = X;
    ans.reverse();
    return ans;
}


int2048 operator +(const int2048 &X,const int2048 &Y) {
    if(X.sign == Y.sign) {
        return Add(X,Y);
    } else {
        int32_t cmp = Compare_abs(X,Y);
        if(cmp == 0)     return 0;
        else if(cmp > 0) return Sub(X,Y);
        else  /*cmp < 0*/return Sub(Y,X);
    }
}

int2048 operator -(const int2048 &X,const int2048 &Y) {
    if(X.sign != Y.sign) {
        return Add(X,Y);
    } else {
        int32_t cmp = Compare_abs(X,Y); // abs_compare of X,Y
        if(cmp == 0)     return 0;
        else if(cmp > 0) return  Sub(X,Y);
        else             return -Sub(Y,X);
    }
}

/**
 * @brief Move data from another vector.
 * 
 */
int2048 &int2048::operator =(int2048 &&tmp) {
    swap(tmp);
    sign = tmp.sign;
    return *this;
}


/**
 * @brief Copy data from another vector.
 * 
 */
int2048 &int2048::operator =(const int2048 &tmp) {
    copy(tmp);
    sign = tmp.sign;
    return *this;
}

/**
 * @brief Instream input for an int2048 object.
 * 
*/
std::istream &operator >>(std::istream &is,int2048 &dst) {
    is >> int2048::buffer;
    dst.resize(0);
    dst.read(int2048::buffer);
    return is;
}

/** 
 * @brief Outstream output for an int2048 object. 
*/
std::ostream &operator <<(std::ostream &os,const int2048 &src) {
    src.print(os);
    return os;
}

/**
 * @brief Reserve space and set sign.
 * It's a private initializing function.
 * 
*/
int2048::int2048(uint64_t cap,bool flag) {
    sign = flag;
    reserve(cap);
}

/// @brief Initialize from long long.
/// Default is value is 0 if not set. 
int2048::int2048(int64_t tmp = 0) {
    reserve(initLen);
    if(!tmp) { // tmp = 0
        sign = false;
        push_back(0);
        return;
    } else {
        if(tmp < 0) {
            sign = true;
            tmp = -tmp;
        } else { // tmp > 0
            sign = false;
        }
        while(tmp) {
            push_back(tmp % base);
            tmp /= base;
        }
    }

}

/// @brief Move construction. 
int2048::int2048(int2048 &&tmp) {
    swap(tmp);
    sign = tmp.sign;
}

/// @brief Copy construction. 
int2048::int2048(const int2048 &tmp) {
    copy(tmp);
    sign = tmp.sign;
}

/// @brief Initialize from std::string.  
int2048::int2048(const std::string &str) {
    read(str);
}





}


#endif

