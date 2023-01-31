#ifndef _DARK_SEGMENT_TREE_H_
#define _DARK_SEGMENT_TREE_H_

#include <stddef.h>
#include <cstring>

namespace dark {


template <class value_t,bool QSUM,bool QMAX>
struct Tnode;

template <class value_t>
struct Tnode <value_t,true,false> {
    value_t sum; /* Sum of the node. */
    value_t tag; /* Forever tag. */
    void initTag() { tag = 0; }
};

template <class value_t>
struct Tnode <value_t,false,true> {
    value_t max; /* Max val. */
    value_t tmx; /* Max tag. */
    void initTag() { }
};

template <class value_t>
struct Tnode <value_t,true,true> : public 
    Tnode <value_t,true,false>,Tnode <value_t,false,true>{
    void initTag() { 
        Tnode<value_t,true,false>::initTag(); 
    }
};


/**
 * @brief Basic template of segment_tree.
 * 
 * @tparam value_t Inner value_type.
 * @tparam N Length of array(1 - base).
 */
template <class value_t,size_t __N> 
class segment_tree {
    // static_assert (QSUM || QMAX,"Don't use empty segment_tree!");

  private:
    using node = Tnode <value_t,true,false>;
    node data[__N << 2]; /* 4 times at most. */
    
    size_t N; /* Length of inner data. */
    #define ls id << 1
    #define rs id << 1 | 1

    /**
     * @brief Build the segment tree with initial array.
     * 
     * @param src Source of data. If nullptr, all data will be set 0.
     * @param id  The index of inner node.
     * @param l   The left  border of the node.
     * @param r   The right border of the node.
     */
    void build(value_t *src,size_t id,size_t l,size_t r) {
        data[id].tag = 0;
        // initTag();
        if(l == r) {
            data[id].sum = (src ? src[l] : 0);
            // initVal();
            return;
        }
        size_t mid = (l + r) >> 1;
        build(src,ls, l , mid );
        build(src,rs,mid + 1,r);
        data[id].sum = data[ls].sum + data[rs].sum;
        // initPushUp();
    }

    /* Add in a range. Optimized by lifelong tagging. */
    void update(size_t id,size_t l,size_t r,
             size_t L,size_t R,value_t val) {
        data[id].sum += (R - L + 1) * val;
        // updateVal(data[id],L,R);
        if(l == L && r == R) {
            return (void) (data[id].tag += val); 
            // return updateTag(data[id],val);
        }

        size_t mid = (l + r) >> 1;
        if(R <= mid)      update(ls, l , mid ,L,R,val);
        else if(L > mid)  update(rs,mid + 1,r,L,R,val);
        else {
            update(ls, l , mid , L , mid ,val);
            update(rs,mid + 1,r,mid + 1,R,val);
        }
    }

    /* Query in a range. Optimized by lifelong tagging. */
    value_t querySUM(size_t id,size_t l,size_t r,
                  size_t L,size_t R,value_t tag) const {
        // static_assert(QSUM == true,"Can't query sum!");

        if(l == L && r == R) return data[id].sum + (R - L + 1) * tag;

        tag += data[id].tag;
        size_t mid = (l + r) >> 1;
        if(R <= mid)     return querySUM(ls, l , mid ,L,R,tag);
        else if(L > mid) return querySUM(rs,mid + 1,r,L,R,tag);
        else return querySUM(ls, l , mid , L , mid ,tag)
                  + querySUM(rs,mid + 1,r,mid + 1,R,tag);  
    }

    #undef ls
    #undef rs
  
  public:

    size_t length() const { return N; }
    size_t size()   const { return N; }

    /**
     * @brief Initialize from an array.
     * 
     * @param src The data source. If null, all data will be set 0. 
     */
    void build(value_t *src = nullptr) {
        return build(src,1,1,N);
    }

    /**
     * @brief Reset the length and initialize from an array.
     * 
     * @param __n Length of inner data. Can't be 0 or it will crash!
     * @param src The data source. If null, all data will be set 0. 
     */
    void build(size_t __n,value_t *src = nullptr) {
        return build(src,1,1,N = __n);
    }

    /**
     * @brief Add a value to range [l,r].
     * 
     * @param l The left  side of the range.
     * @param r The right side of the range.
     * @param val The value to be added.
     */
    void add(size_t l,size_t r,value_t val) {
        return update(1,1,N,l,r,val);
    }

    /**
     * @brief Query the sum in range [l,r].
     * 
     * @param l The left  side of the range.
     * @param r The right side of the range.
     * @return value_t The sum queryed.
     */
    value_t sum(size_t l,size_t r) const {
        return querySUM(1,1,N,l,r,0);
    }

    /**
     * @brief Construct a new segment tree object.
     * 
     * @param __n The initial length.
     * @param src The source of data.
     */
    segment_tree(size_t __n = 0,value_t *src = nullptr) {
        if(bool(N = __n)) build(src);
    }
};

}


#endif
