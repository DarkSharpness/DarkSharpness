#ifndef _NUMBER_CC_
#define _NUMBER_CC_
#include "FFT.cc"
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

int2048 int2048::Sub_abs_at(const int2048 &Y,uint64_t len) {
    #define X (*this)
    int2048 ans(X.size(),X.sign);
    uint64_t ret = 0;
    for(uint32_t i = len ; i < Y.size() ; ++i) {
        ret += X[i] - Y[i];
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
    #undef X
}

/**
 * @brief Addition by 1 in abs value.
 * 
 */
int2048 &selfAdd(int2048 &X) {
    for(auto &it : X) {
        if(++it != int2048::base) return X;
        it = 0;
    }
    X.push_back(1);
    return X;
}

/**
 * @brief Subtraction by 1 in abs value.
 * 
 */
int2048 &selfSub(int2048 &X) {
    for(auto &it : X) {
        if(--it != -1ULL) {
            if(X.size() > 1 && !X.back()) X.pop_back();
            return X;
        }
        it = int2048::base - 1;
    }
    throw "Invalid subtraction!";
}


/**
 * @brief Multiply X and Y by brute force.
 * For Maximum speed, X.size() should be greater than Y.size().
 * Also, ensure that Y.size() <= NTT_threshold .
 * 
 */
int2048 Mult_BF(const int2048 &X,const int2048 &Y) {
    if(!X || !Y) return 0;
    int2048 ans(0,X.sign ^ Y.sign);
    ans.resize(X.size() + Y.size());
    for(uint32_t i = 0 ; i < X.size() ; ++i)
        for(uint32_t j = 0 ; j < Y.size() ; ++j) 
            ans[i + j] += X[i] * Y[j];
    for(uint32_t i = 0 ; i < ans.size() ; ++i) {
        if(ans[i] >= int2048::base) {
            ans[i + 1] += ans[i] / int2048::base;
            ans[i] %= int2048::base;
        }
    }
    if(!ans.back()) ans.pop_back();
    return ans;
}


/**
 * @brief Multiply X and Y by NTT algorithm.
 * 
 */
int2048 Mult_NTT(const int2048 &X,const int2048 &Y) {
    if(!X || !Y) return 0;
    uint32_t len = 1;
    uint32_t pow = 0;
    while(len < X.size() + Y.size()) len <<= 1,++pow;

    // Work out rev
    static std::vector <uint32_t> rev;
    NTT_base::getRev(rev,len);

    /// Work Out A0 and B0
    std::vector <uint64_t> A0;
    std::vector <uint64_t> B0;
    A0.reserve(len); A0 = X; A0.resize(len);
    B0.reserve(len); B0 = Y; B0.resize(len); 


    // Perform reverse operation.
    NTT_base::reverse(&(A0[0]),&(rev[0]),len);
    NTT_base::reverse(&(B0[0]),&(rev[0]),len);
    std::vector <uint64_t> A1 = A0;
    std::vector <uint64_t> B1 = B0;

    // NTT operations
    NTT_base::NTT0(&A0[0],len,0);
    NTT_base::NTT1(&A1[0],len,0);
    NTT_base::NTT0(&B0[0],len,0);
    NTT_base::NTT1(&B1[0],len,0);

    // Merge NTT results
    for(uint32_t i = 0 ; i < len ; ++i) {
        A0[i] = (A0[i] * B0[i]) % int2048::mod[0];
        A1[i] = (A1[i] * B1[i]) % int2048::mod[1];
    }

    // INTT with reverse operation.
    NTT_base::reverse(&A0[0],&rev[0],len);
    NTT_base::reverse(&A1[0],&rev[0],len);
    NTT_base::NTT0(&A0[0],len,1);
    NTT_base::NTT1(&A1[0],len,1);

    // CRT to work out the final A0
    const uint64_t inv[3] = { // Inverses used.
        NTT_base::inverse[0][pow],
        NTT_base::inverse[1][pow],
        1014089499ULL // inverse of mod[1] in mod[0].
    };
    uint64_t ret = 0;
    A0.resize(X.size() + Y.size());
    for(uint32_t i = 0 ; i < A0.size() ; ++i) {
        A0[i] = (A0[i] * inv[0]) % int2048::mod[0];
        A1[i] = (A1[i] * inv[1]) % int2048::mod[1];
        ret += int2048::getMult(A0[i],A1[i],inv[2]);
        A0[i] = ret % int2048::base;
        ret /= int2048::base; // ret = ret / NTTLen
    }

    // Work out answer
    int2048 ans(0,X.sign ^ Y.sign);
    ans.swap(A0);
    if(!ans.back()) ans.pop_back();
    return ans;
}

/**
 * @brief Divide X by Y using binary trial.
 * 
 */
int2048 Div_BF(const int2048 &X,const int2048 &Y) {
    if(Y.size() == 1 && Y.back() == 1) return X; // Y == 1 case.
    // The Final answer.
    int2048 ans(0,X.sign ^ Y.sign);
    ans.resize(X.size() + 1 - Y.size());
    
    int2048 cur = X;
    // TODO : write true binary find.
    uint64_t len = X.size() + 1 - Y.size();
    while(cur >= Y) { // compare until cur < Y.
        while(Y.Compare_abs_at(cur,len)) --len;
        uint64_t l = 1;
        uint64_t r = int2048::base;
        while(l != r) { // binary search in [l,r)
            uint64_t mid = (l + r) >> 1;
            if((Y * mid).Compare_abs_at(cur,len) != 1) {
                l = mid + 1;    // mid valid
            } else { r = mid; } // mid invalid
        } // Terminal : l == r == invalid
        ans[len] = l - 1;
        cur.Sub_abs_at((l - 1) * Y,len); 
    }
    while(!ans.back()) ans.pop_back();
    return ans;
}

/**
 * @brief Divide X by Y using Newton's method.
 * Note that X.size() must be no less than Y's.
 * 
 */
int2048 Div_NT(const int2048 &X,const int2048 &Y) {
    int2048 ans = (X * ~Y) >> (Y.size() << 1);
    int2048 tmp = ans * Y + Y;
    while(Compare_abs(X,tmp) == 1u) {
        selfAdd(ans);
        tmp += Y;
    }
    ans.sign = X.sign ^ Y.sign;
    return ans;
}


}






/**
 * @brief This part includes arithmetic operators for int2048.
 * 
 */
namespace sjtu {

/**
 * @brief Multiply X by base ^ Y
 * Note that Y must be nonegative. 
 * 
 * @return X * base ^ Y
 */
inline int2048 operator <<(const int2048 &X,const uint64_t Y) {
    if(!X) return 0;
    if(!Y) return X;
    int2048 ans(X.size() + Y,X.sign);
    ans.assign(Y,0);
    ans.insert(ans.end(),X.begin(),X.end());
    return ans;
}
/**
 * @brief Divide X by base ^ Y
 * Note that Y must be nonegative. 
 *  
 * @return X * base ^(-Y)
 */
inline int2048 operator >>(const int2048 &X,const uint64_t Y) {
    if(Y >= X.size()) return 0;
    if(!Y) return X;
    int2048 ans(X.size() - Y,X.sign);
    ans.insert(ans.end(),X.begin() + Y,X.end());
    return ans;
}


/**
 * @brief Return the number of  X * (-1).
 * 
 * @return -X
 */
inline int2048 operator -(int2048 &&X) {
    int2048 ans(0,!X.sign);
    ans.swap(X);
    return ans;
}
/**
 * @brief Return the number of X * (-1).
 * If you simply want to multiply X by -1,
 * please use reverse() instead.
 * 
 * @return -X
 */
inline int2048 operator -(const int2048 &X) {
    int2048 ans = X;
    ans.reverse();
    return ans;
}

/**
 * @brief Add X by Y.
 * 
 * @return X + Y
 */
inline int2048 operator +(const int2048 &X,const int2048 &Y) {
    if(X.sign == Y.sign) {
        return Add(X,Y);
    } else {
        int32_t cmp = Compare_abs(X,Y);
        if(cmp == 0)     return 0;
        else if(cmp > 0) return Sub(X,Y);
        else  /*cmp < 0*/return Sub(Y,X);
    }
}
/**
 * @brief Subtract Y from X.
 * 
 * @return X - Y
 */
inline int2048 operator -(const int2048 &X,const int2048 &Y) {
    if(X.sign != Y.sign) {
        return Add(X,Y);
    } else {
        int32_t cmp = Compare_abs(X,Y); // abs_compare of X,Y
        if(cmp == 0)     return 0;
        else if(cmp > 0) return  Sub(X,Y);
        else  /*cmp < 0*/return -Sub(Y,X);
    }
}

/**
 * @brief Multiply X by Y.
 * 
 * @return X * Y
 */
inline int2048 operator *(const int2048 &X,const int2048 &Y) {
    if(X.size() <= int2048::NTT_threshold) {
        return Mult_BF(Y,X);
    } else if(Y.size() <= int2048::NTT_threshold) {
        return Mult_BF(X,Y);
    } else {
        return Mult_NTT(X,Y);
    }
}


/**
 * @brief Divide X by Y.
 * 
 * @return X / Y 
 */
inline int2048 operator /(const int2048 &X,const int2048 &Y) {
    int32_t cmp = Compare_abs(X,Y);
    if(cmp == -1) return 0;
    if(cmp ==  0) return X.sign ^ Y.sign ? -1 : 1;
    if(Y.size() <= int2048::DIV_threshold) {
        return Div_BF(X,Y);
    }
    uint64_t dif = X.size() - Y.size() * 2;
    if(int64_t(dif) < 0) {
        return Div_NT(X,Y);
    } else {
        return Div_NT(X << dif,Y << dif);
    }
}


/**
 * @brief Get inverse in base ^ X.size() * 2
 * 
 * @return 1 / X (in mod = base ^ (X.size() * 2))
 */
int2048 operator ~(const int2048 &X) {
    int2048 top = int2048(1) << (X.size() << 1);
    if(X.size() <= int2048::DIV_threshold) {
        return Div_BF(top,X);
    }
    // half of X.size() with a bias of 5 according to
    // https://www.luogu.com.cn/blog/88403/solution-p5432
    uint32_t hf = (X.size() + 5) >> 1; 
    int2048  Y  = ~(X >> (X.size() - hf)); // highest few bits
    // Newton's Iteration : 2 * (1 / X) - x * (1 / X) ^ 2
    Y = 2 * (Y << (X.size() - hf)) - (X * Y * Y >> (hf << 1)); 
    if(Compare_abs(top,X * Y) == -1) selfSub(Y);
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
    if(!tmp) { // tmp = 0
        sign = false;
        push_back(0);
        return;
    } else {
        reserve(initLen);
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

#endif

