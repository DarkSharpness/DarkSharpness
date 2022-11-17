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
inline void int2048::reverse() {
    sign = !sign;
}


/**
 * @brief Split the 18-bit vector to 6-bit.(DEC)
 * 
 */
std::vector <uint64_t> int2048::split(uint32_t len) const {
    std::vector <uint64_t> ans;
    ans.reserve(len);
    for(auto it : (*this)) {
        ans.push_back(it % int2048::NTTLen);
        it /= int2048::NTTLen;
        ans.push_back(it % int2048::NTTLen);
        ans.push_back(it / int2048::NTTLen);
    }
    ans.resize(len);
    return ans;
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
    // Small optimization...
    if(!!X || !!Y) return 0;
    if(X.size() == 1 && X[0] == 1) return X.sign ? -Y : Y;
    if(Y.size() == 1 && Y[0] == 1) return Y.sign ? -X : X;
    // End of small optimzation

    static uint64_t Y1_bit[int2048::NTT_threshold];
    static uint64_t Y2_bit[int2048::NTT_threshold];
    for(uint32_t j = 0 ; j < Y.size() ; ++j) {
        Y2_bit[j] = Y[j] / int2048::BFLen;    
        Y1_bit[j] = Y[j] % int2048::BFLen;    
    } // static optimization


    #define Y1 Y1_bit[j] // lower  bit of Y
    #define Y2 Y2_bit[j] // higher bit of Y
    std::vector <uint64_t> V((X.size() + Y.size()) << 1); // Double the size...
    for(uint32_t i = 0 ; i < X.size() ; ++i) {
        const uint64_t X2 = X[i] / int2048::BFLen; // X[i] / BFlen (higher bit)
        const uint64_t X1 = X[i] % int2048::BFLen; // X[i] % BFLen (lower  bit)
        for(uint32_t j = 0 ; j < Y.size() ; ++j) {
            V[(i + j) << 1]     += X1 * Y1;
            V[(i + j) << 1 | 1] += X1 * Y2 + X2 * Y1;
            V[(i + j + 1) << 1] += X2 * Y2;
        }
    }
    #undef Y1
    #undef Y2

    
    int2048 ans(0,X.sign ^ Y.sign);
    ans.swap(V);
    uint64_t ret = 0;
    for(uint32_t i = 0 ; i < X.size() + Y.size() ; ++i) {
        if(ans[i << 1 | 1] > int2048::BFLen) {
            ans[(i+1) << 1] += ans[i << 1 | 1] / int2048::BFLen;
            ans[i << 1 | 1] %= int2048::BFLen;
        }
        ret += ans[i << 1] + ans[i << 1 | 1] * int2048::BFLen;
        ans[i]   = ret % NTT_base::base;
        ret     /= NTT_base::base;
    }
    ans.resize(X.size() + Y.size());
    while(!ans.back()) ans.pop_back();
    return ans;
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
        A0[i] = ret % int2048::NTTLen;
        ret /= int2048::NTTLen; // ret = ret / NTTLen
    }

    int2048 ans(0,X.sign ^ Y.sign);
    ret = 0;
    ans.swap(A0); 
    while(!ans.back()) ans.pop_back();
    return ans;
}



}

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
 * @param type 0: mod[0],NTT  || 1 : mod[1],NTT  || \n 
 *             2: mod[0],INTT || 3 : mod[1],INTT ||
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
    return X.back();
}

}

/**
 * @brief This part includes augassign operators.
 * 
 */
namespace sjtu {

int2048& operator *=(int2048 &X,const int2048 &Y) {
    return X = X * Y;
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

int2048 operator *(const int2048 &X,const int2048 &Y) {
    if(X.size() <= int2048::NTT_threshold) {
        return Mult_BF(Y,X);
    } else if(Y.size() <= int2048::NTT_threshold) {
        return Mult_BF(X,Y);
    } else {
        return Mult_NTT(X,Y);
    }
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
 * @param tmp 
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
