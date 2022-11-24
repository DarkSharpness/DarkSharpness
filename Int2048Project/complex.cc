#ifndef _COMPLEX_CC_
#define _COMPLEX_CC_

namespace sjtu {

struct complex {
  public:
    complex(double _r = 0,double _i = 0) : real(_r),imag(_i) {}
    ~complex() = default;

    double real,imag;
    /* The abs value of a complex object. */ 
    inline friend double abs(const complex &X) {
        return X.real * X.real + X.imag * X.imag;
    }
    inline friend complex operator +(const complex &X,const complex &Y) {
        return complex(X.real + Y.real , X.imag + Y.imag);
    }
    inline friend complex operator -(const complex &X,const complex &Y) {
        return complex(X.real - Y.real , X.imag - Y.imag);
    }
    inline friend complex operator *(const complex &X,const complex &Y) {
        return complex(X.real * Y.real - X.imag * Y.imag,
                       X.real * Y.imag + X.imag * Y.real);
    }
    inline friend complex operator /(const complex &X,const complex &Y) {
        double den = abs(Y);
        return complex((X.real * Y.real + X.imag * Y.imag) / den,
                       (X.real * Y.imag - X.imag * Y.real) / den);
    }

    /**
     * @brief  Change a complex object into its conjugate complex number.
     * 
     * @return The conjugate of the previous complex.
     */
    inline complex &conjugate(void) {
        imag = -imag;
        return *this;
    }

    /* Change a complex object into its conjugate complex number. */
    inline friend void conjugate(complex &X) {
        X.imag = -X.imag;
    }

    /*  Return the conjugate complex number. */
    inline friend complex operator ~(const complex &X) {
        return complex(X.real,-X.imag);
    }
    /* Return the conjugate complex number. */
    inline friend complex operator ~(complex && X) {
        return X.conjugate();
    }


    inline friend complex &operator +=(complex &X,const complex & Y) {
        return X = X + Y;
    }
    inline friend complex &operator -=(complex &X,const complex & Y) {
        return X = X - Y;
    }
    inline friend complex &operator *=(complex &X,const complex & Y) {
        return X = X * Y;
    }
    inline friend complex &operator /=(complex &X,const complex & Y) {
        return X = X / Y;
    }


};

}

#endif