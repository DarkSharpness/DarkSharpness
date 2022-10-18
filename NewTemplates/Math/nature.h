#include <General/basic.h>
#ifndef _DARK_NATURE_H_
#define _DARK_NATURE_H_


namespace dark {

namespace private_space { 
template <class _VT> 
inline constexpr _VT MAX(const _VT &V1,const _VT &V2) {
    if(V1 < V2) return V2;
    else return V1;
}
template <class _VT> 
inline constexpr _VT MIN(const _VT &V1,const _VT &V2) {
    if(V1 < V2) return V1;
    else return V2;
}

}


template <class _VT>
inline constexpr _VT Max(const _VT& V) {
    return V;
}

/// @brief Return the maximum value in the list 
template <class _VT,class ..._VTs>
constexpr _VT Max(const _VT& arg,const _VTs& ...args) {
    return private_space::MAX(arg,Max(args...));
}
/// @brief Return the maximum value in the range 
template <class iterator> 
constexpr auto MaxIn(iterator begin,
                     iterator end) {
    auto ans = *begin;
    for(++begin; begin != end ; ++begin) {
        if(*begin > ans) ans = *begin;
    }
    return ans;
}

template <class _VT>
inline constexpr _VT Min(const _VT& V) {
    return V;
}
/// @brief Return the minimum value in the list 
template <class _VT,class ..._VTs>
constexpr _VT Min(const _VT& arg,const _VTs& ...args) {
    return private_space::MIN(arg,Min(args...));
}

/// @brief Return the minimum value in the range 
template <class iterator> 
constexpr auto MinIn(const iterator& begin,
                     const iterator& end) {
    iterator it = begin;
    auto ans = *it;
    for(++it; it != end ; ++it) {
        if(*it < ans) ans = *it;
    }
    return ans;
}

/**
 * @brief Find the ans of pow(base,exponent)
 * in O(log exponent) time. \n 
 * The base can be integers,float numbers,Matrices...
 * Note that exponent must be a positive integer,
 * stored in a integer-style type(e.g. int,long long),
 * supporting %>>=% operation and %&% operation.
 * Otherwise you may get unexpected outcome.
 * 
 * 
 * @param base     base of the expression 
 * @param exponent exponent of the expression 
 * @return pow(base,exponent)
 */
template <class value_type,class integer>
constexpr value_type quick_pow(value_type base,
                               integer exponent) {
    bool flag = false;
    //if(exponent < 0) throw("");
    value_type ans;
    while(exponent > 0) {
        if(exponent & 1) {
            if(!flag) {
                flag = true;
                ans = base;
            }
            else ans *= base;
        }
        base *= base;
        exponent >>= 1;
    }
    return ans;
}

/**
 * @brief Find the ans of pow(base,exponent) % modulus
 * in O(log exponent) time. \n 
 * The base can only be integers with % operatoion
 * Note that exponent must be a non-negative integer,
 * stored in a integer-style type(e.g. int,long long),
 * supporting ">>=" operation and "&"" operation.
 * Otherwise you may get unexpected outcome.
 * 
 * @param base     base of the expression 
 * @param exponent exponent of the expression 
 * @param mod      modulus  of the expression
 * @return pow(base,exponent)
 */
template <class integer1,class integer2>
constexpr integer1 quick_pow(integer1 base,
                             integer2 exponent,
                             integer1 mod) {
    integer1 ans = 1;
    while(exponent > 0) {
        if(exponent & 1) {
            ans *= base;
            ans %= mod;
            if(!ans) break;
        }
        base *= base;
        base %= mod;
        exponent >>= 1;
    }
    return ans;
}

}

#endif