#ifndef __DATA_PALLOCATOR_H__
#define __DATA_PALLOCATOR_H__
#include <vector>
/**
 * @brief Auto manager of pointers of specific value.
 * 
 * @tparam value_t The value_type of the ptr.
 */
template<typename value_t>
class Pallocator : std::allocator <value_t>{//personalized allocator
    private:
    
    typedef value_t* valueptr; 
    size_t _size;             //Record sizeof the elements
    std::vector <valueptr> v; //Recycling container.
    public:
    /**
     * @brief 
     * 
     * @return valueptr 
     */
    valueptr apply(){
        ++_size;
        if(!v.empty()){
            v.pop_back();
            return *v.cend();
        } 
        return allocate(1);
    }
    //reuse an element
    void recycle(valueptr _ptr){
        _size--;
        v.push_back(_ptr);
    }
    //
    void shrink_to_fit(){
        v.shrink_to_fit();
    }
    //Initializaton
    Pallocator(){
        _size=0;
    }
    //Delete the data
    ~Pallocator(){//clear the ptrs in vector
        for(valueptr _I:v) deallocate(_I,1);
        v.clear();
    }
};


#endif