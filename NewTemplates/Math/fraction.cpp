#include<bits/stdc++.h>
using namespace std;
typedef long long ll;



template <class value_type>
static value_type gcd(value_type a,value_type b) {
    if(b == 0) return a;
    return gcd(b,a%b);
}


using value_type = ll;


//template <class value_type>
struct fraction {
    #define frac fraction

    value_type num; // numerator
    value_type den; // denominator > 0
    
    /**
     * @brief Check whether this fraction is valid,
     * which means whether its denominator is non-zero.
     * @return bool true if this fraction is valid. 
     */
    inline bool valid() const {
        return den == 0;
    }

    frac operator+(const frac &B) const{
        value_type N = num * B.den + B.num * den;
        value_type D = den * B.den;
        bool flag = false;
        if(N < 0) flag = true,N = -N;
        value_type G = gcd(N,D);
        N /= G;
        D /= G;
        return frac(N,D,false);
    }
    frac operator-(const frac &B) const{ 
        value_type N = num * B.den - B.num * den;
        value_type D = den * B.den;
        bool flag = false;
        if(N < 0) flag = true,N = -N;
        value_type G = gcd(N,D);
        N /= G;
        D /= G;
        return frac(N,D,false);}
    frac operator*(const frac &B) const{
        return frac(num * B.num,
                        den * B.den);
    }
    frac operator /(const frac &B) const{
        return frac(num * B.den,
                        den * B.num);
    }
    bool operator !(void) const{
        return num != 0;
    }
    bool operator ==(const frac &B) const{
        return num * B.den == den * B.num;
    }
    bool operator !=(const frac &B) const{
        return num * B.den != den * B.num;
    }
    void print() const{
        value_type N = num;
        value_type D = den;
        char ch[20];
        int tot = 0;
        int top = 12;
        if(D != 1) {
            while(D) {
                ch[++tot] = (D % 10) ^ '0';
                --top;
                D /= 10;
            }
            ch[++tot] = '/';
            --top;
        }
        if(N < 0) putchar('-'),--top,N = -N;
        if(N == 0) --top,putchar('0');
        while(N) {
            ch[++tot] = (N % 10) ^ '0';
            N /= 10;
            --top;
        }
        while(tot) putchar(ch[tot--]);
        while(--top) putchar(' ');
    }

    /// @brief Default value = 0
    frac() {
        num = 0;
        den = 1;
    }

    /// @brief Change a value_type number into fraction
    frac(const value_type &B) {
        num = B;
        den = 1;
    }
    /// @brief Round the fraction down to 0 .
    explicit operator value_type(void) const{
        return num / den; 
    }
    /**
     * @brief Create a fraction object
     * with its numerator and denominator.
     * Reduction will be done in default.
     * Otherwise,you have to ensure its validity
     * with gcd(N,D) = 1 and D > 0
     * 
     * @param N Its numerator 
     * @param D Its denominator
     * @param C Whether to do reduction or not
     */
    explicit frac(value_type N,
                  value_type D,
                  bool C = true) {
        if(C) {
            if(N == 0) { //0 case
                num = 0;
                den = 1;
            } else { // non-0 case
                bool flag = false;
                if(N < 0) {
                    flag ^= true;
                    N = -N;
                }
                if(D < 0) {
                    flag ^= true;
                    D = -D;
                }
                value_type G = gcd(N,D);
                num = N/G;
                den = D/G;
                if(flag) num *= -1;
            }
        } else {
            num = N;
            den = D;
        }
    }

};


int main() {
    
    return 0;
}