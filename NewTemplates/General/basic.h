#include<new>
#include<string.h>

#ifndef _DARK_BASIC_H_
#define _DARK_BASIC_H_

namespace dark{
    typedef unsigned long long size_type;
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



    
}
#endif