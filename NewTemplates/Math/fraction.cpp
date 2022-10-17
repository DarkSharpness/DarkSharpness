#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a,ll b) {
    if(b == 0) return a;
    return gcd(b,a%b);
}

using value_type = ll;


//template <value_type>
struct fraction {
    value_type num;
    value_type den;
    
    fraction operator+(const fraction &B) const{
        return fraction(num * B.den + B.num * den,
                        den * B.den);
    }
    fraction operator-(const fraction &B) const{ 
        return fraction(num * B.den - B.num * den,
                        den * B.den);
    }
    fraction operator*(const fraction &B) const{
        return fraction(num * B.num,
                        den * B.den);
    }
    fraction operator /(const fraction &B) const{
        return fraction(num * B.den,
                        den * B.num);
    }
    bool operator ==(const fraction &B) const{
        return num * B.den == den * B.num;
    }
    bool operator !=(const fraction &B) const{
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
    fraction() {
        num = 0;
        den = 1;
    }
    fraction(const value_type &B) {
        num = B;
        den = 1;
    }
    explicit fraction(value_type A,value_type B) {
        if(A == 0) {
            num = 0;
            den = 1;
        }
        else {
            bool flag = false;
            if(A < 0) {
                flag ^= true;
                A = -A;
            }
            if(B < 0) {
                flag ^= true;
                B = -B;
            }
            value_type G = gcd(A,B);
            num = A/G;
            den = B/G;
            if(flag) num *= -1;
        }
    }

};


int main() {
    
    return 0;
}