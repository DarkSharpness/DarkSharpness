#include<General/basic.h>
#include<Data/Allocator.h>


namespace dark {

template <class value_type>
class dynamic_array{
    private:
    using value_cref = const value_type &;
    using value_rref = value_type &&;
    using value_ref  = value_type &;
    using value_ptr  = value_type *;
    allocator <value_type> A;

    value_ptr head; // start of data
    value_ptr tail; // end of data
    value_ptr term; // end of capacity
 
    /// @brief Expand the %array% to the target size. 
    ///        Ensure that target is no less than current size.
    inline void __expand(size_type target) {
        value_ptr __head = A.allocate(target);
        memcpy(__head,head,sizeof(value_type)*(tail-head));
        tail = __head + (tail - head);
        A.deallocate(head,(term - head));
        term = __head + (term - head);
    }

    public:
    /// @return The total of elements in the %array%.
    inline constexpr size_type size() const{
        return tail - head;
    }
    /// @return The maximum elements the %array% can hold
    ///         before next allocation.
    inline constexpr size_type capacity() const{
        return term - head;
    }

    /**
     * @brief Add an element to the back of
     * the %array% in amortized O(1) time.
     * 
     * @param value The value to be added to the back.
     */
    inline void push_back(value_cref value) {
        if(tail == term) {
            if(head == tail) {__expand(1);}
            else {__expand((term - tail) << 1);}
        }
        *(tail++) = value;
    }
    inline void push_back(value_rref value) {
        emplace_back(value);
    }
    template<class ..._Args>
    inline void emplace_back(_Args && ...args) {
        if(tail == term) {
            if(head == tail) {__expand(1);}
            else {__expand((term - tail) << 1);}
        }
    }


    /// @brief Shrink the size of the %array%
    /// by 1 in O(1) time without safety check.        
    inline void pop_back() {
        --tail;
    }

    

    /**
     * @brief A read/write subscript access to  
     * data in this array without safety check.
     *  
     * @param index 
     * @return value_ref 
     */
    inline constexpr value_ref  operator[](size_type index) {
        return head[index];   
    }

    /**
     * @brief A read-only subscript access to  
     * data in this array without safety check.
     *  
     * @param index 
     * @return value_ref 
     */
    inline constexpr value_cref operator[](size_type index) const{
        return head[index];
    }


};

}


#include <General/inout.h>
using namespace dark;


int main() {
    

    return 0;
}