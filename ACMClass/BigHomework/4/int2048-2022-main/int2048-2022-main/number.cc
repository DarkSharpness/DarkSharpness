#ifndef _NUMBER_CC_
#define _NUMBER_CC_
#include "number.h"

namespace sjtu {

/**
 * @brief This part include all the constants
 * and non-int2048 functions
 * 
 */

// Number map for print out
const char *num_map[] = {
    "00","01","02","03","04","05","06","07","08","09",
    "10","11","12","13","14","15","16","17","18","19",
    "20","21","22","23","24","25","26","27","28","29",
    "30","31","32","33","34","35","36","37","38","39",
    "40","41","42","43","44","45","46","47","48","49",
    "50","51","52","53","54","55","56","57","58","59",
    "60","61","62","63","64","65","66","67","68","69",
    "70","71","72","73","74","75","76","77","78","79",
    "80","81","82","83","84","85","86","87","88","89",
    "90","91","92","93","94","95","96","97","98","99"
};
const uint32_t Max_bit = 100;            // The maximum of a bit
const uint32_t Bit_len = 2;              // Maximum length of a bit
const uint32_t mod     = 4194304001;     // mod number
const uint32_t root[2] = {2383,1760094}; // root[0]*root[1] = mod + 1

/// @brief Fast Pow for NTT only
/// Possible optimization : prework base case
/// @param expo  The exponent of the expression
/// @return uint64_t The value of pow(base,exponenent)
constexpr uint64_t fastPow(uint64_t base,uint32_t expo) {
    uint64_t res = 1;
    while(expo) {
        if(expo & 1) {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        expo >>= 1;
    }
    return res;
}


/**
 * @brief This part include all the
 * simplification functions
 * 
 */


/** 
 * @brief Reference to idx'th element
 * in the num vector.
 * @param idx The index of the element.
 * @return Reference to idx'th element.
*/
uint8_t& int2048::operator [](uint32_t idx) {
    return num[idx];
}
/** 
 * @brief Const reference to idx'th  
 * element in the num vector.
 * @param idx The index of the element.
 * @return Const reference to idx'th element.
*/
uint8_t  int2048::operator [](uint32_t idx) const{
    return num[idx];
}
/** 
 * @brief Const reference to idx'th  
 * element in the num vector with safe check.
 * If idx >= size() , 0 will be returned.
 * @param idx The index of the element.
 * @return Const reference to idx'th element.
*/
uint8_t  int2048::operator ()(uint32_t idx) const{
    return idx >= size() ? 0u : num[idx];
}


/// @brief Clear useless zeros in num.
void int2048::clear_zero() {
    while(num.size() >= 1 && !num.back()) {
        num.pop_back();
    }
}
/// @brief Push an element to the back of 
/// the number vector within.
/// @param val The value to be inserted 
void int2048::push_back(uint8_t val) {
    num.push_back(val);
}
/// @brief Resize the num vector. 
void int2048::resize(uint64_t siz) {
    num.resize(siz);
}
/// @brief Reserve space for the num vector.
void int2048::reserve(uint64_t siz) {
    num.reserve(siz);
}
/// @return The size of the num vector.
uint32_t int2048::size() const {
    return num.size();
}
/// @brief Change to zero
void int2048::zero() {
    sign = false;
    num.resize(1,0);
}

/**
 * @brief Add X by Y in X's sign
 * (which means sgn(X)*(abs(X)+abs(Y)) ).
 * @return int2048 The sum of abs(X),abs(Y) 
 * with the sign of X
 */
int2048 Add(const int2048 &X,const int2048 &Y) {
    int2048 ans(0,0);
    ans.sign = X.sign;
    uint32_t len = std::max(X.size(),Y.size());
    ans.reserve(len + 1);
    uint8_t ret = 0;
    for(uint32_t i = 0 ; i != len ; ++i) {
        ret += X(i) + Y(i);
        if(ret >= Max_bit) {
            ans.push_back(ret - Max_bit);
            ret = 1;
        } else {
            ans.push_back(ret);
            ret = 0;
        }
    }
    if(ret) ans.push_back(ret);
    return ans;
}
/**
 * @brief Subtract X from Y in X's sign
 * (which means sgn(X)*(abs(X)-abs(Y)) ).
 * @return int2048 The diff of abs(X),abs(Y).
 * The sign is the same as X if(X > Y),
 * different from X otherwise
 */
int2048 Sub(const int2048 &X,const int2048 &Y) {
    int32_t temp = Compare_abs(X,Y);
    int2048 ans(0,0);
    if(temp == 1) {
        ans.sign = X.sign;
        uint32_t ret = 0;
        ans.reserve(X.size());
        for(uint32_t i = 0 ; i != X.size() ; ++i) {
            ret += X[i] - Y(i);
            if(ret >= Max_bit) { // Overflow case
                ans.push_back(ret + Max_bit);
                ret = -1;
            } else {
                ans.push_back(ret);
                ret = 0;
            }
        }
        ans.clear_zero();
    } else if(temp == -1) {
        ans.sign = !X.sign;
        uint32_t ret = 0;
        ans.reserve(Y.size());
        for(uint32_t i = 0 ; i != Y.size() ; ++i) {
            ret += Y[i] - X(i);
            if(ret >= Max_bit) { // Overflow case
                ans.push_back(ret + Max_bit);
            } else {
                ans.push_back(ret);
            }
        }
        ans.clear_zero();
    } else {ans.zero();}
    return ans;
}
/**
 * @brief Compare the abs value of X and Y
 * in O(log(X*Y)) time.
 * @return 0 if X == Y , 1 if X > Y , -1 if X < Y
 */
int32_t Compare_abs(const int2048 &X,const int2048 &Y) {
    if(X.size() > Y.size()) return  1;
    if(X.size() < Y.size()) return -1;
    for(uint32_t i = X.size() ; i != -1u ; --i) {
        if(X[i] > Y[i]) return  1;
        if(X[i] < Y[i]) return -1;      
    }
    return 0;
}


/**
 * @brief This part includes all logical
 * operators of int2048
 *  
 */


/// @brief Judge if X == Y in O(log(X*Y)) time.
/// @return bool true if X == Y,false if X != Y
bool operator ==(const int2048 &X,const int2048 &Y) {
    if(X.sign != Y.sign || X.size() != Y.size()) {
        return false;
    }
    for(uint32_t i = X.size()-1 ; i != -1u ; --i) {
        if(X[i] != Y[i]) return false;
    }
    return true;
}
/// @brief Judge if X != Y in O(log(X*Y)) time.
/// @return bool true if X != Y,false if X == Y
bool operator !=(const int2048 &X,const int2048 &Y) {
    if(X.sign != Y.sign || X.size() != Y.size()) {
        return true;
    }
    for(uint32_t i = X.size()-1 ; i != -1u ; --i) {
        if(X[i] != Y[i]) {
            return true;
        }
    }
    return false;
}

/// @brief Judge if X < Y in O(log(X*Y)) time.
/// @return bool true if X < Y,false if X >= Y
bool operator <(const int2048 &X,const int2048 &Y) {
    if(X.sign != Y.sign) {
        return X.sign > Y.sign;
    } else if(X.size() != Y.size()) {
        return X.sign ? X.size() > Y.size() :
                        X.size() < Y.size() ;
    }
    for(uint32_t i = X.size()-1 ; i != -1u ; --i) {
        if(X[i] != Y[i]) {
            return X.sign ? X[i] > Y[i] :
                            X[i] < Y[i] ;
        }
    }
    return false; // == case
}
/// @brief Judge if X <= Y in O(log(X*Y)) time.
/// @return bool true if X <= Y,false if X > Y
bool operator <=(const int2048 &X,const int2048 &Y) {
    if(X.sign != Y.sign) {
        return X.sign > Y.sign;
    } else if(X.size() != Y.size()) {
        return X.sign ? X.size() > Y.size() :
                        X.size() < Y.size() ;
    }
    for(uint32_t i = X.size()-1 ; i != -1u ; --i) {
        if(X[i] != Y[i]) {
            return X.sign ? X[i] > Y[i] :
                            X[i] < Y[i] ;
        }
    }
    return true; // == case
}

/// @brief Judge if X > Y in O(log(X*Y)) time.
/// @return bool true if X > Y,false if X <= Y
bool operator >(const int2048 &X,const int2048 &Y) {
    if(X.sign != Y.sign) {
        return X.sign < Y.sign;
    } else if(X.size() != Y.size()) {
        return X.sign ? X.size() < Y.size() :
                        X.size() > Y.size() ;
    }
    for(uint32_t i = X.size()-1 ; i != -1u ; --i) {
        if(X[i] != Y[i]) {
            return X.sign ? X[i] < Y[i] :
                            X[i] > Y[i] ;
        }
    }
    return false; // == case
}
/// @brief Judge if X >= Y in O(log(X*Y)) time.
/// @return bool true if X >= Y,false if X < Y
bool operator >=(const int2048 &X,const int2048 &Y) {
    if(X.sign != Y.sign) {
        return X.sign < Y.sign;
    } else if(X.size() != Y.size()) {
        return X.sign ? X.size() < Y.size() :
                        X.size() > Y.size() ;
    }
    for(uint32_t i = X.size()-1 ; i != -1u ; --i) {
        if(X[i] != Y[i]) {
            return X.sign ? X[i] < Y[i] :
                            X[i] > Y[i] ;
        }
    }
    return true; // == case
}

/// @brief Judge if X == 0 in O(1) time.
/// @return bool true if X != 0,false elsewise.
bool operator !(const int2048 &X) {
    return !X.sign && !X.num.back();
}



/**
 * @brief This part includes all arithmetic
 * operators of int2048
 * 
 */

int2048& operator -(int2048 &X) {
    X.sign = !X.sign;
    return X;
}

int2048& operator -(int2048 &&X) {
    X.sign = !X.sign;
    return X;
}

/// @brief Work out X+Y in O(log(X*Y)) time.
/// @return int2048_t value of X+Y
int2048 operator +(const int2048 &X,const int2048 &Y) {
    if(X.sign == Y.sign) {
        return Add(X,Y);
    } else {
        return Sub(X,Y);
    }
}

/// @brief Work out X+Y in O(log(X*Y)) time.
/// @return int2048_t value of X+Y
int2048 operator -(const int2048 &X,const int2048 &Y) {
    if(X.sign != Y.sign) {
        return Add(X,Y);
    } else {
        return Sub(X,Y);
    }
}


int2048 operator *(const int2048 &X,const int2048 &Y) {
    // TODO
    return 0;
}

/**
 * @brief This part includes basic in/out functions 
 * and type conversion of int2048
 * 
 */



std::istream &operator >>(std::istream &is,int2048 &dst) {
    static std::string buffer;
    is >> buffer;
    dst = int2048(buffer);
    return is;
}
std::ostream &operator <<(std::ostream &os,const int2048 &src) {
    if(src.sign) os << '-';
    uint32_t i = src.size() - 1;
    if(src[i] < 10) os << char(src[i] ^ '0');
    else            os << num_map[src[i]];
    while(i) {
        os << num_map[src[--i]]; 
    }
    return os;
}


/**
 * @brief This part includes all construction
 *  functions and move/copy functions of int2048.
 * 
 */


/// @brief Intialize a number as 0
int2048::int2048() {
    sign = false;
    reserve(10);
    push_back(0);
}

/// @brief Initialize with capacity = cap
/// and size = siz.
int2048::int2048(uint64_t cap,uint64_t siz) {
    num.reserve(cap);
    num.resize(siz);
}

/// @brief Initalize a number from long long 
int2048::int2048(long long tmp) {
    reserve(10);
    if(tmp == 0) {
        sign = false;
        push_back(0);
    } else {
        if(tmp < 0) {
            tmp = -tmp;
            sign = true;
        } else {
            sign = false;
        }
        while(tmp) {
            push_back(tmp % Max_bit);
            tmp /= Max_bit;
        }
    }
    std::cout << "Construct by long long!\n";
}


/// @brief Move the memory of a number. 
int2048::int2048(int2048 &&tmp) {
    sign = tmp.sign;
    num.swap(tmp.num);
    // std::cout << "Move Construct!\n";
}

/// @brief Construct from a string
int2048::int2048(const std::string &str) {
    num.reserve((str.size() + 1) >> 1);
    if(str.front() == '-') sign = true;
    else                   sign = false;
    bool flag = false;
    uint8_t tmp = 0;
    for(int i = str.size() - 1 ; i >= sign ; --i) {
        if(flag) {
            tmp += (str[i] ^ '0') * 10;
            num.push_back(tmp);
            tmp = 0;
        } else {
            tmp = str[i] ^ '0';
        }
        flag = !flag;
    }
    if(tmp) num.push_back(tmp);
    std::cout << "Construct from string!\n";
}

}
#endif