#ifndef _COMPLEX_HPP_
#define _COMPLEX_HPP_

#include "../include/basic.hpp"
#include <cmath>

namespace dark {



template <class value_t = double>
struct complex {
    // using value_t =  double;
    value_t real;
    value_t imag;

    ~complex() = default;
    /* Initialize with real part and imaginery part.*/
    complex(value_t _r = 0.0,value_t _i = 0.0) : real(_r),imag(_i) {}
    
    /* Initialize with another complex number. */
    // template <class value_t_2>
    // complex(const complex <value_t_2> &rhs) : real(rhs.real),imag(rhs.imag) {}

    /* Assign operation. */
    complex &operator =(const complex &rhs) {
        real = rhs.real;
        imag = rhs.imag;
        return *this;
    }


    /* Return the square of abs.*/
    inline value_t abs2() const {return real * real + imag * imag;}    
    /* Return the square of abs.*/
    friend inline value_t abs2(const complex &rhs) {return rhs.abs2();}

    /* Return the abs value. */
    inline value_t abs() const {return sqrt(abs2());}
    /* Return the abs value. */
    friend inline value_t abs(const complex &rhs)  {return rhs.abs();}

    /* Conjugate the complex number. 
       It will reverse the imaginery part.*/
    inline complex &conjugate() {imag = -imag;return *this;} 
    /* Return conjugate of the value. */
    friend inline complex conjugate(complex &&rhs) {
        return rhs.conjugate();
    }
    /* Return conjugate of the value. */
    friend inline complex conjugate(const complex &rhs) {
        return complex(rhs).conjugate();
    }


    /* Set the argument of a complex number in given length(default). */
    inline void set(double arg,value_t len = 1.0) {
        real = len * cos(arg);
        imag = len * sin(arg);
    }
    /* Return the argumnet of a complex number.
       The argument ranges from -pi/2 to pi/2.  */
    inline double argument() {
        return atan(imag / real);
    }



    /* Arbitrary addition assign. */
    inline complex &operator +=(const complex &rhs) {
        real += rhs.real;
        imag += rhs.imag;
        return *this;
    }
    /* Arbitrary addition. */
    friend inline complex operator +(complex lhs,const complex &rhs) {
        return lhs += rhs;
    }

    /* Arbitrary subtraction assign. */
    inline complex &operator -=(const complex &rhs) {
        real -= rhs.real;
        imag -= rhs.imag;
        return *this;
    }
    /* Arbitrary subtraction. */
    friend inline complex operator -(complex lhs,const complex &rhs) {
        return lhs -= rhs;
    }

    /* Arbitrary multiplication assign.
       Note that it is the same as lhs = lhs * rhs. */
    inline complex &operator *=(const complex &rhs) {
        return *this = *this * rhs;
    }
    /* Arbitrary multiplication. */
    friend inline complex operator *(const complex &lhs,const complex &rhs) {
        return complex(lhs.real * rhs.real - lhs.imag * rhs.imag,
                       lhs.real * rhs.imag + lhs.imag * rhs.real);
    }
    /* Arbitrary division assign.
       Note that it is the same as lhs = lhs * rhs. */
    inline complex &operator /=(const complex &rhs) {
        return *this = *this / rhs;
    }
    /* Arbitrary division. */    
    friend inline complex operator /(const complex &lhs,const complex &rhs) {
        value_t tmp = rhs.abs2();
        return complex((lhs.real * rhs.real + lhs.imag * rhs.imag) / tmp,
                       (lhs.real * rhs.imag - lhs.imag * rhs.real) / tmp);
    }
};


}

#endif
