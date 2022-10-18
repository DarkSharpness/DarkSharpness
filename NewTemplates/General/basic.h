#include<new>
#include<string.h>

#ifndef _DARK_BASIC_H_
#define _DARK_BASIC_H_

namespace dark{


template <typename _VT> 
inline bool greater(const _VT& _v1,const _VT& _v2){
    return _v1 > _v2;
}
template <typename _VT> 
inline bool smaller(const _VT& _v1,const _VT& _v2){
    return _v1 < _v2;
}
template <typename _VT> 
inline bool no_greater(const _VT& _v1,const _VT& _v2){
    return _v1 <= _v2;
}
template <typename _VT> 
inline bool no_smaller(const _VT& _v1,const _VT& _v2){
    return _v1 >= _v2;
}

#define Iter(it,begin,end) for(auto it = begin; it != end ; ++it)
#define Loop(it,begin,end) for(auto it = begin; it <= end ; ++it)
#define until(condition) while(!(condition))
#define unless(condition) if(!(condition))
#define RIter(it,begin,end) for(auto it = begin ; it != end ; --it)
#define RLoop(it,begin,end) for(auto it = begin ; it >= end ; --it)
using size_type = unsigned int;


namespace private_space { // Don't use this namespace unless neccesary!
template <class _VT> 
inline constexpr _VT MAX(const _VT &V1,const _VT &V2) {
    if(V1 > V2) return V1;
    else return V2;
}
}

template <class _VT>
inline constexpr _VT Max(const _VT& V) {
    return V;
}

template <class _VT,class ..._VTs>
constexpr _VT Max(const _VT& arg,const _VTs& ...args) {
    return private_space::MAX(arg,Max(args...));
}

template <class iterator> 
constexpr auto MaxIn(const iterator& begin,
                     const iterator& end) {
    iterator it = begin;
    auto ans = *it;
    for(++it; it != end ; ++it) {
        if(*it > ans) ans = *it;
    }
    return ans;
}

}
#endif