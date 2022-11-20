#ifndef _NTT_CC
#define _NTT_CC
#include "number.h"

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
 * Namely "Butterfly Operation"
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
 * @param type 0: NTT || 1: INTT 
 *             
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

/**
 * @brief Key operation of NTT algorithm.
 * 
 * @param A    The array of the original value.  
 * @param rev  The array of reverse pair.
 * @param len  The length of the NTT array.
 * @param type 0: NTT || 1: INTT
 *             
 */
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


#endif
