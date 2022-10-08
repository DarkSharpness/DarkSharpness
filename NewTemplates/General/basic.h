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


}
#endif