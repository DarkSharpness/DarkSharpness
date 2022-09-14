#ifndef _DARK_VECTOR_
#define _DARK_VECTOR_ 1

#include<Data/allocator.h>
namespace dark{


typedef int _VT;

//An Simple Vector Without useless function
class vector {
    private:
    typedef _VT* v_ptr; 
    typedef const _VT* c_ptr;
    typedef _VT& v_ref;
    typedef const _VT& c_ref;
    //typedef unsigned long long size_type;
    
    struct vector_base : allocator <_VT> {
        v_ptr head;
        v_ptr tail;
        v_ptr end;
        void expand(size_type _size){
            v_ptr __tmp = allocate(_size? _size : 1);
            memcpy(__tmp,head,
                  sizeof(_VT)*(tail-head));
            deallocate(head,tail-head);
            tail = __tmp + (tail-head);
            head = __tmp ;
            end  = __tmp - _size;
            return;
        }
    }T;
    #define tail T.tail
    #define head T.head
    #define end  T.end

    public:
    void push_back(c_ref _Val) {
        if(tail == end) 
           T.expand(tail-head <<1); 
        *(tail++) = _Val;
    }
    void pop_back() {
        --tail;
    }
    void resize(size_type _size) {
        if(!_size) return ;
        if(_size > end-head) {
            T.expand(_size);    
        }
        tail = head + _size;
    }
    void reserve(size_type _size) {
        if(!_size) return ;
        if(_size > end-head) {
            T.expand(_size);    
        }
    } 
    size_type size()const{
        return tail-head;
    }
    size_type capacity()const{
        return end-head;
    }
    
    vector operator=(const vector _Vec) {
        resize(_Vec.size());
        memcpy(head,_Vec.head,sizeof(_VT)*_Vec.size());
        return *this;
    }
    bool operator ==(const vector _Vec) const{
        if(size() != _Vec.size()) return false;
        v_ptr __v1 = head,
              __v2 = _Vec.head;
        while(__v1 != tail) {
            if(*__v1 != *__v2) return false;
            ++__v1,++__v2;
        }
        return true;
    }
    bool operator !=(const vector _Vec) const{
        if(size() != _Vec.size()) return true;
        v_ptr __v1 = head,
              __v2 = _Vec.head;
        while(__v1 != tail) {
            if(*__v1 != *__v2) return true;
            ++__v1,++__v2;
        }
        return false;
    }
    
    bool compare(const vector _Vec) const{
        
    }
    vector() {
        tail = head = end = NULL;
    }
};



}
#endif