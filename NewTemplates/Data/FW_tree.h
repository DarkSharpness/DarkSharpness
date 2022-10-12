#include <General/basic.h>

#ifndef _DARK_FWTREE_H_
#define _DARK_FWTREE_H_


namespace dark {

/**
 * @brief Find the lowest bit value of x.
 * 
 * @param x A binary-encoded integer.
 * (for example: int,unsigned long long)
 */
template <class T>
static T lowbit(const T& x){
    return x & (-x);
}


/**
 * @brief Maintain a sequence  with : 
 * Fast-Single-Value-Add in O(log SIZE) 
 * Fast-Prefix-Sum-Query in O(log SIZE) . \n 
 * You can create other templates based on this one. 
 * NOTE that the index start from 1. 
 * 
 * 
 * @tparam value_type The value_type of elements.
 * @tparam SIZE       The maximum number of elements.
 */
template <class value_type,size_type SIZE>
class FW_tree {
    private:
    using value_cref = const value_type &;
    value_type data[SIZE];
    
    /**
     * @brief A reference type of value. \n 
     * Operations on the value of index at idx
     * are all O(log SIZE)
     * 
     */
    class iterator {
        private:
        size_type idx;
        FW_tree <value_type,SIZE> * tptr;
        public:
        operator value_type() {
            return tptr->query(idx)-tptr->query(idx-1);
        }
        /// @brief No recommended.If possible,use += or -= instead.  
        value_type operator=(value_cref val) {
            tptr->add(idx,val-tptr->query(idx)+tptr->query(idx-1));
            return val;
        }
        /// @brief Add at this location.
        void operator +=(value_cref val) {
            tptr->add(idx,val);
        }
        void operator -=(value_cref val) {
            tptr->add(idx,-val);
        }
        iterator(int _idx,FW_tree <value_type,SIZE> * t) {
            idx  = _idx;
            tptr = t;
        }
    };
    public:
    /**
     * @brief Add a certain value at a specific location 
     * in O(log SIZE) time.
     * 
     * @param idx The index of the inserted element. 
     * @param val The value of the inserted element.
     */
    inline void add(size_type idx,value_cref val) {
        while(idx <= SIZE) {
            data[idx] += val;
            idx += lowbit(idx);
        }
    }
    /**
     * @brief Calculate the prefix-sum of idx ( data[1] ~ data[idx] )
     * in O(log SIZE) time.
     * 
     * @param idx The idx to be queryed.
     * @return value_type The prefix-sum queried.
     */
    inline value_type query(size_type idx) const{
        value_type sum = 0;
        while(idx) {
            sum += data[idx];
            idx ^= lowbit(idx);
        }
        return sum;
    }
    
    inline iterator operator[](size_type idx) {
        return iterator(idx,this);
    }
    
    /**
     * @brief Clear the FW_tree in O(n) time.
     * 
     */
    inline void clear() {
        memset(data,0,sizeof(data));
    }
    //Work as what you think.
    inline size_type size() const{
        return SIZE;
    }

    /**
     * @brief Initialize a new FW_tree object
     * with a certain sequence 
     * in O(SIZE).
     * Note that the original sequence won't be cleared.
     * The current operation serves as adding one element
     * in each certain possition.
     * You may clear it by using clear() function.
     * 
     * @param begin Begin Iterator
     * @param end   End   Iterator
     */
    template <class iterator>
    inline void initialize(iterator begin,iterator end) { 
        size_type cnt = 0;
        Iter(it,begin,end) {
            ++cnt;
            data[cnt] += (*it);
            if(cnt + lowbit(cnt) <= SIZE)
                data[cnt+lowbit(cnt)] += data[cnt];
        }
        while(cnt <= SIZE) {
            ++cnt;
            if(cnt + lowbit(cnt) <= SIZE)
                data[cnt+lowbit(cnt)] += data[cnt];
        }
    }

    

    FW_tree() {
    }

    /**
     * @brief Initialize a new FW_tree object
     * with a certain sequence 
     * in O(SIZE).
     * 
     * @param begin Begin Iterator
     * @param end   End   Iterator
     */
    template <class iterator>
    FW_tree(iterator begin,iterator end) {
        unsigned int cnt = 0;
        Iter(it,begin,end) {
            ++cnt;
            data[cnt] += (*it);
            if(cnt + lowbit(cnt) <= SIZE)
                data[cnt+lowbit(cnt)] += data[cnt];
        }
        while(cnt <= SIZE) {
            ++cnt;
            if(cnt + lowbit(cnt) <= SIZE)
                data[cnt+lowbit(cnt)] += data[cnt];
        }
    }

};

}

/* test use

#include <General/inout.h>
using namespace dark;
const int N = 20;
int a[N];
int n,m;
    
FW_tree <int,N> F;


void print() {
    for(int i = 1 ; i <= n ; ++i) {
        write("# ",F.query(i)-F.query(i-1));
    }
    puts("");
}


int main() {
    read(n,m);
    Iter(i,0,n) read(a[i]);
    F.initialize(a,a+n);
    print();
    while(m--) {
        int opt,x,y;
        read(opt,x,y);
        if(opt == 1) {
            F.add(x,y);
        } else {
            write("#\n",F.query(y)-F.query(x-1));
        }
        print();
    }
    return 0;
}
*/



#endif