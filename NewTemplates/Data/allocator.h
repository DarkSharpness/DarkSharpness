#include<General/basic.h>

namespace dark{

 
//typedef int _VT;


//An easy allocator
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