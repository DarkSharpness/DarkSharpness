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
    
    constexpr static uint64_t lenb          = 3;   // log10(base)
    constexpr static uint64_t base          = 1e3; // base of FFT
    constexpr static uint64_t FFT_threshold = 00;  // FFT_threshold
    constexpr static uint64_t maxLen        = 20;  // maximum length for FFT
    constexpr static uint64_t initLen       = 6;   // initial length for vector
    static complex root[maxLen];
    constexpr static uint64_t unit[lenb] = {1,10,100};

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

#ifndef _FFT_CC
#define _FFT_CC


/**
 * @brief This part includes all NTT functions.
 * 
 */
namespace sjtu {



/**
 * @brief Perform reverse operator on A.
 * Namely "Butterfly Operation"
 * 
 */
inline void FFT_base::reverse(complex *A,uint64_t *rev,uint32_t len) {
    for(uint32_t i = 0 ; i < len; ++i){
        if(i < rev[i]) std::swap(A[i],A[rev[i]]);
    }
}

/**
 * @brief Initlize the FFT_base's roots.
 * Called only once in initializer.
 * 
 */
inline void FFT_base::FFT_init() {
    for(uint32_t i = 0 ; i != maxLen ; ++i) {
        root[i].setangle(PI/(1ll << i));
    }
}

/**
 * @brief FFT function part.
 * 
 * @param A    Complex data array.
 * @param len  Length of the operation.
 * @param type 0 : FFT(default) || 1 : IFFT
 */
void FFT_base::FFT(complex *A,uint32_t len,bool type = 0) {
    int cnt = 0;
    for(uint32_t i = 1; i < len; i <<= 1) {
        complex w = root[cnt++]; // unit root
        if(type) w.conjugate();
        for(uint32_t j = 0; j < len; j += (i << 1)) {
            //temp.real=1.0 , temp.imaginery=0.0;
            complex tmp(1,0);
            for(uint32_t k = 0; k < i;++k) {
                complex x = A[j + k] ;
                complex y = A[j + k + i] * tmp;
                A[j + k]     = x + y;
                A[j + k + i] = x - y;
                tmp *= w;
            }
        }
    }
}
/**
 * @brief As its name suggests.
 * 
 */
inline void FFT_base::IFFT(complex *A,uint32_t len) {
    FFT(A,len,true);
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
 * Ensure that X.size() >= Y.size()
 * 
 * @return int2048 sgn(X) * (abs(X) + abs(Y)).
 */
int2048 Add(const int2048 &X,const int2048 &Y) {
    int2048 ans(X.size() + 1,X.sign);
    uint64_t ret = 0;
    for(uint32_t i = 0; i < X.size() ; ++i) {
        ret += X[i] + Y(i);
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
 * Ensure that abs(X) > abs(Y).
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
 * 
 * @return int2048 X * Y in brute force time.
 */
int2048 Mult_BF(const int2048 &X,const int2048 &Y) {
    if(!X || !Y) return 0;

    int2048 ans(0,X.sign ^ Y.sign);
    ans.resize(X.size() + Y.size());
    // cache friendly for X.
    for(uint32_t i = 0 ; i < X.size() ; ++i)
        for(uint32_t j = 0 ; j < Y.size() ; ++j)
            ans[i + j] += X[i] * Y[j];
    for(uint32_t i = 0 ; i < ans.size() ; ++i) {
        if(ans[i] > FFT_base::base) {
            ans[i + 1] += ans[i] / FFT_base::base;
            ans[i]     %= FFT_base::base;
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
    uint32_t len = 1;
    while(len < X.size() + Y.size()) len <<= 1;

    // Work out rev
    std::vector <uint64_t> rev(len);
    for(uint32_t i = 0 ; i < len ; ++i) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * len >> 1);
    }

    static std::vector <complex> A;
    static std::vector <complex> B;

    A.assign(len,complex(0,0));
    for(uint32_t i = 0 ; i != X.size() ; ++i) A[i].real = X[i];
    B.assign(len,complex());
    for(uint32_t i = 0 ; i != Y.size() ; ++i) B[i].real = Y[i];


    // Perform reverse operation.
    FFT_base::reverse(&A[0],&rev[0],len);
    FFT_base::reverse(&B[0],&rev[0],len);

    // Perform NTT
    FFT_base::FFT(&A[0],len);
    FFT_base::FFT(&B[0],len);

    for(uint32_t i = 0 ; i < len ; ++i) 
        A[i] *= B[i];

    FFT_base::reverse(&A[0],&rev[0],len);
    FFT_base::IFFT(&A[0],len);
    int2048 ans(0,X.sign ^ Y.sign);
    ans.swap(rev); // getSpace from rev vector.
    ans.assign(X.size() + Y.size(),0);

    // move the data from real to answer.
    for(uint32_t i = 0 ; i < ans.size() ; ++i) {
        ans[i] += uint64_t(A[i].real / double(len) + 0.5);
        if(ans[i] >= int2048::base) {
            ans[i + 1] += ans[i] / int2048::base;
            ans[i] -= ans[i + 1] * int2048::base; 
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




}


/**
 * @brief This part includes arithmetic operators for int2048.
 * 
 */
namespace sjtu {

/**
 * @brief X expands by base ^ Y
 *  
 * 
*/
int2048 operator <<(const int2048 &X,const uint64_t Y) {
    int2048 ans(X.size() + Y,X.sign);
    ans.insert(ans.end(),Y,0);
    ans.insert(ans.end(),X.begin(),X.end());
    return ans;
}

/**
 * @brief X shrinks by base ^ Y
 *  
 * 
*/
int2048 operator >>(const int2048 &X,const uint64_t Y) {
    if(Y >= X.size()) return 0;
    int2048 ans(X.size() - Y,X.sign);
    ans.insert(ans.begin(),X.begin() + Y,X.end());
    return ans;
}


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
        return X.size() >= Y.size() ?  Add(X,Y) : Add(Y,X);
    } else {
        int32_t cmp = Compare_abs(X,Y);
        if(cmp == 0)     return 0;
        else if(cmp > 0) return Sub(X,Y);
        else  /*cmp < 0*/return Sub(Y,X);
    }
}

int2048 operator -(const int2048 &X,const int2048 &Y) {
    if(X.sign != Y.sign) {
        return X.size() >= Y.size() ?  Add(X,Y) : Add(Y,X);
    } else {
        int32_t cmp = Compare_abs(X,Y); // abs_compare of X,Y
        if(cmp == 0)     return 0;
        else if(cmp > 0) return  Sub(X,Y);
        else             return -Sub(Y,X);
    }
}

int2048 operator *(const int2048 &X,const int2048 &Y) {
    if(std::min(X.size(),Y.size()) <= int2048::FFT_threshold) {
        if(X.size() > Y.size()) return Mult_BF(X,Y);
        else                    return Mult_BF(Y,X);
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
 * @brief Convert to bool in O(1) time.
 *  
 */
int2048::operator bool() const{
    return back();
}

/**
 * @brief Convert to double in O(log size()) time.
 * This works because precision of double is only 2^53,
 * which is smaller than base ^ 3.
 * 
 */
int2048::operator double() const{
    double tmp = 0;
    if(size() <= 3) {
        for(auto it = rbegin() ; it != rend() ; ++it)
            tmp = tmp * FFT_base::base + double(*it);
        return tmp;
    }
    else {
        for(uint32_t i = size() - 1; i != size() - 4 ; --i) 
            tmp = tmp * FFT_base::base + double((*this)[i]);
        uint64_t ret = size() - 3;
        double base  = FFT_base::base;
        while(ret) {
            if(ret) tmp *= base;
            base *= base;
            ret >>= 1;
        }
        return tmp;
    }

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



struct initializer : FFT_base{
    initializer() {
        FFT_init();
        // std::ios::sync_with_stdio(false);
    }
}_INITIALIZER;



}

#endif

int main() {
    sjtu::int2048 x,y;
    std::cin >> x >> y;
    std::cout << x * y;
    return 0;
}