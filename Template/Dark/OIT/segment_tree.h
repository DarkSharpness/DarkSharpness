#ifndef _DARK_SEGMENT_TREE_H_
#define _DARK_SEGMENT_TREE_H_

#include <stddef.h>
#include <cstring>

namespace dark {

/**
 * @brief Basic template of segment_tree.
 * 
 * @tparam value_t Inner value_type.
 * @tparam N Length of array(1 - base).
 */
template <class value_t,size_t __N> 
class segment_tree {
  private:
    struct node {
        value_t val; /* Value of the node. */
        value_t tag; /* Forever tag. */
    } data[__N << 2]; /* 4 times at most. */

    const unsigned N; /* Length of inner data. */
    #define ls id << 1
    #define rs id << 1 | 1

    /* Build the segment tree with initial array. */
    void build(value_t *src,unsigned id,unsigned l,unsigned r) {
        data[id].tag = 0;
        if(l == r) {
            data[id].val = src[l];
            return;
        }
        unsigned mid = (l + r) >> 1;
        build(src,ls, l , mid );
        build(src,rs,mid + 1,r);
        data[id].val = data[ls].val + data[rs].val;
    }

    /* Add in a range. Optimized by lifelong tagging. */
    void add(unsigned id,unsigned l,unsigned r,
             unsigned L,unsigned R,value_t val) {
        data[id].val += (R - L + 1) * val;
        if(l == L && r == R) { data[id].tag += val; return; }

        unsigned mid = (l + r) >> 1;
        if(R <= mid)      add(ls, l , mid ,L,R,val);
        else if(L > mid)  add(rs,mid + 1,r,L,R,val);
        else {
            add(ls, l , mid , L , mid ,val);
            add(rs,mid + 1,r,mid + 1,R,val);
        }
    }
    /* Query in a range. Optimized by lifelong tagging. */
    value_t query(unsigned id,unsigned l,unsigned r,
                  unsigned L,unsigned R,value_t tag) const {
        if(l == L && r == R) return data[id].val + (R - L + 1) * tag;

        unsigned mid = (l + r) >> 1;
        tag += data[id].tag;
        if(R <= mid)     return query(ls, l , mid ,L,R,tag);
        else if(L > mid) return query(rs,mid + 1,r,L,R,tag);
        else return query(ls, l , mid , L , mid ,tag)
                  + query(rs,mid + 1,r,mid + 1,R,tag);  
    }
    #undef ls
    #undef rs
  
  public:
    
    /**
     * @brief Build from a given array (1-base).
     * 
     * @param src If src == nullptr,nothing is done.
     */
    void build(value_t *src) { if(src) return build(src,1,1,N); }

    /**
     * @brief Add a value to range [l,r].
     * 
     * @param l The left  side of the range.
     * @param r The right side of the range.
     * @param val The value to be added.
     */
    void update(unsigned l,unsigned r,value_t val) {
        return add(1,1,N,l,r,val);
    }

    /**
     * @brief Query the sum in range [l,r].
     * 
     * @param l The left  side of the range.
     * @param r The right side of the range.
     * @return value_t The sum queryed.
     */
    value_t sum(unsigned l,unsigned r) const {
        return query(1,1,N,l,r,0);
    }

    segment_tree(unsigned length,value_t *src = nullptr) 
        : N(length) {
        // memset(data,0,sizeof(data));
        build(src);
    }

};

}


#endif
