#ifndef _FFT_CC_
#define _FFT_CC_
#include "int2048.h"

#if NUMBER_TYPE == 1



namespace sjtu {

/* Initialize function for FFT.Called once! */
inline void FFT_base::FFT_init() {
    for(size_t i = 0 ; i < FFT_maxBit ; ++i) {
        root[i].set(PI / double(1ULL << i));
    }
}

void FFT_base::FFT(complex *A,size_t len,bool opt = 0) {
    size_t cnt = 0;
    for(size_t i = 1 ; i < len ; i <<= 1) {
        complex wn = root[cnt++]; // unit root
        if(opt) conjugate(wn);
        for(size_t j = 0 ; j < len ; j += (i << 1)) {
            complex w(1.0,0.0);
            for(size_t k = 0 ; k < i ; ++k , w *= wn) {
                complex x = A[j | k] ;
                complex y = A[j | k | i] * w;
                A[j | k]     = x + y;
                A[j | k | i] = x - y;
            }
        }
    }

}

inline void FFT_base::IFFT(complex *A,size_t len) {
    return FFT(A,len,1);
}

int2048 &Mult_FT(int2048 &X,const int2048 &Y) {
    X.sign ^= Y.sign;
    size_t len = 2;
    size_t maxLen = X.size() + Y.size();
    while(len < maxLen) len <<= 1;
    static array <complex> A;
    A.resize(len);
    for(size_t i = 0 ; i < len ; ++i) {
        A[i].real = i >= X.size() ? 0.0 : X[i];
        A[i].imag = i >= Y.size() ? 0.0 : Y[i];
    }

    static array <size_t> rev;
    static array <size_t> rev;
    int2048::getRev(rev,len);

    Number_base()



}



}

#endif
#endif
