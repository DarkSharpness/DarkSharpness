#include<General/basic.h>
#ifndef _DARK_ALLOCATOR_H_
#define _DARK_ALLOCATOR_H_
namespace dark{

//An easy allocator... Isn't it?
template <typename _VT>
struct allocator{
    typedef _VT* v_ptr;
    v_ptr allocate(size_type _n) const{
        return static_cast<v_ptr>(::operator new(_n * sizeof(_VT)));
    }
    void deallocate(v_ptr _p,size_type _n) const{
        ::operator delete(_p,_n * sizeof(_VT));
    }
};


}
#endif