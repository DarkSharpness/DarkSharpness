#ifndef _FFT_CC
#define _FFT_CC

#include "number.h"

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
        // complex w = root[cnt++]; // unit root
        // if(type) w.conjugate();
        for(uint32_t j = 0; j < len; j += (i << 1)) {
            //temp.real=1.0 , temp.imaginery=0.0;
            complex tmp(1,0);
            for(uint32_t k = 0; k < i;++k) {
                tmp.setangle(double(PI * k) / i);
                if(type) tmp.conjugate();
                complex x = A[j + k] ;
                complex y = A[j + k + i] * tmp;
                A[j + k]     = x + y;
                A[j + k + i] = x - y;
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
