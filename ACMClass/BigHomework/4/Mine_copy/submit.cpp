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
    static inline std::vector <uint32_t> getRev(uint32_t len);
    static inline uint64_t getMult(uint64_t A0,uint64_t A1,uint64_t inv);
    
    constexpr static uint64_t NTT_threshold = 0;
    constexpr static uint64_t mod[2]  = {2281701377,3489660929}; // mod number
    constexpr static uint64_t lenb    = 6;   // base len in decimal
    constexpr static uint64_t base    = 1e6; // base of int2048 = 10 ^ lenb
    constexpr static uint64_t initLen = 6;   // initial length reserved
    constexpr static uint64_t MaxLen  = 1 << 21; // Maximum possible NTT length
    // constexpr static uint64_t rate    = 3;    // compressing rate
    constexpr static uint64_t BFLen   = 1e9;  // Brute Force length
    // constexpr static uint64_t root[2][2] = {     // root and inv root
    // 3,(mod[0] + 1) / 3,3,(mod[1] + 1) / 3
    // };  // common root
    constexpr static uint64_t unit[lenb] = { // units below base
        1,
        10,
        100,
        1000,
        10000,
        100000,
        // 1000000,
    };
    constexpr static uint64_t root[2][2][22]= {
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
    
    /**
     * @brief Least length for NTT.
     * Note that 2 * threshold * base should be less than 2 ^ 64. 
     * 
     */
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
    inline uint64_t operator ()(uint64_t idx)  const;
    friend int2048 operator ~(const int2048 &X);


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
    friend int32_t Compare_abs(const int2048 &X,const int2048 &Y);
    void read(const std::string &str);
    void print(std::ostream &os) const;
    void move(std::vector <uint64_t> &tmp);
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

#ifndef _NTT_CC
#define _NTT_CC

/**
 * @brief This part includes all NTT functions.
 * 
 */
namespace sjtu {

/**
 * @brief Built-in fast pow function.
 * 
 * @return uint64_t Pow(base,pow) % mod_type.
 */
inline uint64_t NTT_base::fastPow0(uint64_t base,uint64_t pow) {
    uint64_t ans = 1;
    while(pow) {
        if(pow & 1) ans = (ans * base) % mod[0];
        base = (base * base) % mod[0];
        pow >>= 1;
    }
    return ans;
}

inline uint64_t NTT_base::fastPow1(uint64_t base,uint64_t pow) {
    uint64_t ans = 1;
    while(pow) {
        if(pow & 1) ans = (ans * base) % mod[1];
        base = (base * base) % mod[1];
        pow >>= 1;
    }
    return ans;
}

/**
 * @brief As Below:
 * A0 + x * mod[0] = A1 + y * mod[1] = C < mod[0] * mod[1]. \n 
 * Then : y = (A0 - A1) ^ inv(mod[1]) (in mod[0]).\n 
 *  
 * 
 * @return uint64_t 
 */
inline uint64_t NTT_base::getMult(uint64_t A0,uint64_t A1,uint64_t inv) {
    if(A0 == A1) return A0;
    else return (A0 - A1 + mod[0] * 2) * inv % mod[0] * mod[1] + A1;  
}

/**
 * @brief Work out the rev vector.
 * 
 */
inline std::vector <uint32_t> NTT_base::getRev(uint32_t len) {
    std::vector <uint32_t> rev(len);
    for(uint32_t i = 0 ; i < len ; ++i) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * len >> 1);
    }
    return rev;
}

/**
 * @brief Perform reverse operator on A.
 * Namely "Butterfly Operation"
 * 
 */
inline void NTT_base::reverse(uint64_t *A,uint32_t *rev,uint32_t len) {
    for(uint32_t i = 0 ; i < len; ++i){
        if(i < rev[i]) std::swap(A[i],A[rev[i]]);
    }
}


/**
 * @brief Key operation of NTT algorithm.
 * 
 * @param A    The array of the original value.  
 * @param rev  The array of reverse pair.
 * @param len  The length of the NTT array.
 * @param type 0: NTT || 1: INTT 
 *             
 */
void NTT_base::NTT0(uint64_t *A,uint32_t len,bool type) {
    uint32_t cnt = 0;
    for(uint32_t i = 1; i < len; i <<= 1) {
        // uint64_t wn = fastPow0(root[0][type],(mod - 1)/(i << 1));
        uint64_t wn = root[0][type][cnt++];
        for(uint32_t j = 0; j < len; j += (i << 1)) {
            uint64_t w = 1; // current w for NTT.
            for(uint32_t k = 0; k < i; ++k) {
                uint64_t x = A[j + k];
                uint64_t y = A[j + k + i] * w % mod[0];
                A[j + k]     = (x + y) % mod[0];
                A[j + k + i] = (x - y +  mod[0]) % mod[0];
                w = w * wn % mod[0];
            }
        }
    }
}

/**
 * @brief Key operation of NTT algorithm.
 * 
 * @param A    The array of the original value.  
 * @param rev  The array of reverse pair.
 * @param len  The length of the NTT array.
 * @param type 0: NTT || 1: INTT
 *             
 */
void NTT_base::NTT1(uint64_t *A,uint32_t len,bool type) {
    uint32_t cnt = 0;
    for(uint32_t i = 1; i < len; i <<= 1) {
        // unit root for NTT.
        // uint64_t wn = fastPow1(root[1][type],(mod[1] - 1)/(i << 1));
        uint64_t wn = root[1][type][cnt++];
        for(uint32_t j = 0; j < len; j += (i << 1)) {
            uint64_t w = 1; // current w for NTT.
            for(uint32_t k = 0; k < i; ++k) {
                uint64_t x = A[j + k];
                uint64_t y = A[j + k + i] * w % mod[1];
                A[j + k]     = (x + y) % mod[1];
                A[j + k + i] = (x - y +  mod[1]) % mod[1];
                w = w * wn % mod[1];
            }
        }
    }
}

}


#endif
#ifndef _NUMBER_CC_
#define _NUMBER_CC_

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
inline void int2048::reverse() {
    sign = !sign;
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
    uint64_t j = sign;
    while(str[j] == '0') ++j;
    if(!str[j]) { // 0 case.
        sign = false;
        push_back(0);
        return;
    }
    reserve(1 + (str.size() - j) / lenb);
    uint64_t i    = str.size();
    uint64_t cnt  = 0;
    uint64_t ret  = 0;
    while(i-- != j) { // Loop in [sign,str.size())
        ret += unit[cnt] * (str[i] ^ '0');
        if(++cnt == lenb) {
            push_back(ret);
            ret = cnt = 0;
        } else {
        }
    }
    if(cnt) push_back(ret);
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
    for(uint32_t i = 0 ; i < size() - 1 ; ++i) {
        uint64_t ret = (*this)[size() - 2 - i];
        for(uint32_t j = lenb - 1 ; j != -1u ; --j) {
            buffer[i * lenb + j] = (ret % 10) ^ '0';
            ret /= 10;
        }
    }
    os << buffer;
}


/**
 * @brief Judge whether abs(X) > abs(Y) in O(log(X*Y)) time.\n 
 * Naturally,it satisfies that Compare_abs(X,Y) = -Compare_abs(Y,X).
 * 
 * @return 1  if abs(X) > abs(Y) ||
 *         0  if abs(X) = abs(Y) ||
 *         -1 if abs(X) < abs(Y) ||
 */
int32_t Compare_abs(const int2048 &X,const int2048 &Y) {
    if(X.size() != Y.size()) {
        return X.size() > Y.size() ? 1 : -1;
    }
    for(uint32_t i = X.size() - 1 ; i != -1u ; --i) {
        if(X[i] != Y[i]) {
            return X[i] > Y[i] ? 1 : -1; 
        }
    }
    return 0;
}


/**
 * @brief Add X by Y in X's sign.
 * 
 * @return int2048 sgn(X) * (abs(X) + abs(Y)).
 */
int2048 Add(const int2048 &X,const int2048 &Y) {
    uint32_t len = std::max(X.size(),Y.size());
    int2048 ans(len + 1u,X.sign);
    uint64_t ret = 0;
    for(uint32_t i = 0; i < len ; ++i) {
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
    for(uint32_t i = 0 ; i < X.size() ; ++i) {
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




/**
 * @brief Multiply X and Y by brute force.
 * For Maximum speed, X.size() should be greater than Y.size().
 * Also, ensure that Y.size() <= NTT_threshold .
 * 
 * @return int2048 X * Y in brute force time.
 */
int2048 Mult_BF(const int2048 &X,const int2048 &Y) {
    return 0;
}





/**
 * @brief Multiply X and Y by NTT algorithm.
 * 
 * @return int2048 
 */
int2048 Mult_NTT(const int2048 &X,const int2048 &Y) {
    uint32_t len = 1;
    while(len < X.size() + Y.size()) len <<= 1;
    std::vector <uint32_t> rev = NTT_base::getRev(len);
    std::vector <uint64_t> A0;
    std::vector <uint64_t> B0;
    A0.reserve(len);
    A0 = X;
    A0.resize(len);
    B0.reserve(len);
    B0 = Y;
    B0.resize(len); 
    // Perform operation.
    NTT_base::reverse(&(A0[0]),&(rev[0]),len);
    NTT_base::reverse(&(B0[0]),&(rev[0]),len);
    std::vector <uint64_t> A1 = A0;
    std::vector <uint64_t> B1 = B0;

    NTT_base::NTT0(&A0[0],len,0);
    NTT_base::NTT1(&A1[0],len,0);
    NTT_base::NTT0(&B0[0],len,0);
    NTT_base::NTT1(&B1[0],len,0);

    for(uint32_t i = 0 ; i < len ; ++i) {
        A0[i] = (A0[i] * B0[i]) % int2048::mod[0];
        A1[i] = (A1[i] * B1[i]) % int2048::mod[1];
    }

    NTT_base::reverse(&A0[0],&rev[0],len);
    NTT_base::reverse(&A1[0],&rev[0],len);
    NTT_base::NTT0(&A0[0],len,1);
    NTT_base::NTT1(&A1[0],len,1);

    const uint64_t inv[3] = {
        NTT_base::fastPow0(len,NTT_base::mod[0] - 2),
        NTT_base::fastPow1(len,NTT_base::mod[1] - 2),
        NTT_base::fastPow0(NTT_base::mod[1],NTT_base::mod[0] - 2)
    };

    uint64_t ret = 0;

    for(uint32_t i = 0 ; i < X.size() + Y.size() ; ++i) {
        A0[i] = (A0[i] * inv[0]) % int2048::mod[0];
        A1[i] = (A1[i] * inv[1]) % int2048::mod[1];
        ret += int2048::getMult(A0[i],A1[i],inv[2]);
        A0[i] = ret % int2048::base;
        ret /= int2048::base; // ret = ret / NTTLen
    }

    int2048 ans(0,X.sign ^ Y.sign);
    ret = 0;
    ans.swap(A0); 
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
    for(uint32_t i = 0 ; i != X.size() ; ++i) {
        if(X[i] != Y[i]) return false;
    }
    return true;
}

/// @return bool true if X != Y
inline bool operator !=(const int2048 &X,const int2048 &Y) {
    if(X.sign != Y.sign || X.size() != Y.size()) {
        return true;
    }
    for(uint32_t i = 0 ; i != X.size() ; ++i) {
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
    return !X.back();
}

}

/**
 * @brief This part includes augassign operators.
 * 
 */
namespace sjtu {
int2048& operator +=(int2048 &X,const int2048 &Y) {return X = X + Y;}
int2048& operator -=(int2048 &X,const int2048 &Y) {return X = X - Y;}
int2048& operator *=(int2048 &X,const int2048 &Y) {return X = X * Y;}
int2048& operator /=(int2048 &X,const int2048 &Y) {return X = X / Y;}
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

int2048 operator <<(const int2048 &X,const uint64_t Y) {
    if(!X) return 0;
    int2048 ans(X.size() + Y,X.sign);
    ans.assign(Y,0);
    ans.insert(ans.end(),X.begin(),X.end());
    return ans;
}

int2048 operator >>(const int2048 &X,const uint64_t Y) {
    if(Y >= X.size()) return 0;
    int2048 ans(X.size() - Y,X.sign);
    ans.insert(ans.end(),X.begin() + Y,X.end());
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

int2048 operator *(const int2048 &X,const int2048 &Y) {
    if(X.size() <= int2048::NTT_threshold) {
        return Mult_BF(Y,X);
    } else if(Y.size() <= int2048::NTT_threshold) {
        return Mult_BF(X,Y);
    } else {
        return Mult_NTT(X,Y);
    }
}




int2048 operator /(const int2048 &X,const int2048 &Y) {
    int32_t cmp = Compare_abs(X,Y);
    if(cmp == -1) return 0;
    if(cmp ==  0) return X.sign ^ Y.sign ? -1 : 1;
    uint64_t dif = X.size() - Y.size() * 2;

    if(int64_t(dif) < 0) dif = 0;

    int2048 ans = ((X << dif) * ~(Y << dif)) 
                  >> (2 * (dif + Y.size()));
    
    ans.sign = false;
    
    // Small adjustments
    int2048 tmp = ans + 1;
    while(Compare_abs(tmp * Y,X) != 1) {
        ans = tmp;
        tmp = tmp + 1;
    }
    while(Compare_abs(ans * Y,X) == 1) {
        ans = ans - 1;
    }
    ans.sign = X.sign ^ Y.sign;
    return ans;
}




/**
 * @brief Get inverse.
 * 
 */
int2048 operator ~(const int2048 &X) {
    #define base int2048::base
    if(X.size() == 1) {
        int2048 ans(0,0);
        uint64_t i = base * base / X[0];
        while(i) {
            ans.push_back(i % base);
            i /= base;
        }
        return ans;
    } else if(X.size() == 2) {
        int2048 ans(0,0);
        constexpr uint64_t N = base * base * base;
        uint64_t div = X[0] + X[1] * base;
        // Make sure base < div
        uint64_t i = (N / div) * base + ((N % div) * base) /div;
        while(i) {
            ans.push_back(i % base);
            i /= base;
        }
        return ans;
    }
    uint32_t hf = 1 + (X.size() >> 1); // half of X.size()
    int2048 Y(0,0);
    Y.insert(Y.end(),X.end() - hf,X.end());
    Y = ~Y;
    return (2 * Y << (X.size() - hf)) - (X * Y * Y >> (hf * 2)); 
    #undef base
}


}

/**
 * @brief This includes all other operators and construction
 * functions of int2048.
 * 
 */
namespace sjtu {

/**
 * @brief Move data from another vector.
 * 
 */
int2048 &int2048::operator =(int2048 &&tmp) {
    if(this == &tmp) return *this;
    swap(tmp);
    sign = tmp.sign;
    return *this;
}


/**
 * @brief Copy data from another vector.
 * 
 */
int2048 &int2048::operator =(const int2048 &tmp) {
    if(this == &tmp) return *this;
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
 *  
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

/**
 * @brief Initialize from a long long object.
 * Default value is zero.
 * 
 */
int2048::int2048(int64_t tmp = 0) {
    reserve(initLen);
    if(!tmp) { // tmp = 0
        sign = false;
        push_back(0);
        return;
    } else {
        if(tmp < 0) {
            sign = true;
            tmp  = -tmp;
        } else { // tmp > 0
            sign = false;
        }
        while(tmp) {
            push_back(tmp % base);
            tmp /= base;
        }
    }

}

/**
 * @brief Move construction.
 * 
 * @param tmp 
 */
int2048::int2048(int2048 &&tmp) {
    swap(tmp);
    sign = tmp.sign;
}

/**
 * @brief Copy construction.
 * 
 */
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

