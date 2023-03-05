#ifndef _DARK_MAP_H_
#define _DARK_MAP_H_

#include "allocator.h"

#include <cstddef>
#include <cstdlib>
#include <functional>

namespace dark {

/* Struct part. */
namespace tree {


/* BW_Tree color */
enum struct Color : bool { BLACK = 0 , WHITE = 1 };


struct node_base;
using baseptr = node_base *;


inline bool is_root(const node_base *__p) noexcept;
template <bool dir>
inline bool is_dir (const node_base *__p) noexcept;
template <bool dir>
void advance(baseptr &__p) noexcept;


/* BW_Tree node base */
struct node_base {
    Color   color;
    baseptr parent;
    baseptr son[2];

    /* Return the direction of this branch. */
    inline bool dir() noexcept { return this != parent->son[0]; }

    /* Whether this is on the __d branch of parent.  */
    inline bool dir(bool __d) noexcept { return this == parent->son[__d]; }

    /* Return the brother node. It requires existence of parent node. */
    inline baseptr bro() noexcept { return this->parent->son[dir(0)]; }

    node_base() noexcept 
        : color(Color::WHITE),parent(this),son({nullptr,nullptr}) {}
};


/**
 * @brief The base for iterator of BW_Tree.
 * 
 * @tparam is_const Whether it's a const iterator. 
 */
template <bool is_const>
struct iterator_base {
  protected:
    using U = std::conditional_t <is_const,const node_base,node_base>;
    using baseptr = U *;
    baseptr ptr;

  public:
    /* Force to pass a pointer. */
    iterator_base(baseptr __p) noexcept : ptr(__p) {}

    iterator_base(const iterator_base <false> &rhs) noexcept : ptr(rhs.ptr) {}

    iterator_base & operator = (const iterator_base <false> &rhs) 
    noexcept { ptr = rhs.ptr; return *this; }

    iterator_base &operator ++ () noexcept
    { advance <1> (ptr); return *this; }

    iterator_base &operator -- () noexcept
    { advance <0> (ptr); return *this; }

    iterator_base operator ++ (int) noexcept 
    { iterator_base temp = *this; advance <1> (ptr); return temp; }

    iterator_base operator -- (int) noexcept 
    { iterator_base temp = *this; advance <0> (ptr); return temp; }

    baseptr base() const { return ptr; }

};


/* BW_Tree node for given value_t(pair <key_t,T>). */
template <class value_t>
struct node : public node_base {
    value_t data;
    node() noexcept = default;
    node(value_t &&__d) noexcept : data(std::move(__d)) {}
    node(const value_t &__d)     : data(__d)            {}
};


}


/* Function part. */
namespace tree {


/* Whether the node is root/header node or not. */
inline bool is_root(const node_base *__p) noexcept 
{ return __p->parent->parent == __p; }


/* Whether the node is header node or not. */
inline bool is_header(const node_base *__p) noexcept 
{ return is_root(__p) && __p->color == Color::WHITE; }


/**
 * @brief Whether the node is in the given branch of its parent.
 * Note that if current node is root , it returns false.
 * 
 * @tparam dir The target direction of the node.
 * @param __p Pointer to current node.
 * @return || 0 if root or on different branch || 1 otherwise ||
 */
template <bool dir>
inline bool is_dir(const node_base *__p) noexcept
{ return !is_root(__p) && __p->dir(dir); }



/**
 * @brief Advance toward target direcition by one step.
 * 
 * @tparam dir Target direction.
 * @param __p The pointer to advance.
 */
template <bool dir>
void advance(baseptr &__p) noexcept { 
    // if(!__p) return ; /* Error ? */
    if(__p->son[dir]) { /* Downward */
        __p = __p->son[dir];
        while(__p->son[!dir]) __p = __p->son[!dir];
    } else { /* Upward. */
        while(is_dir <dir> (__p)) __p = __p->parent;
        __p = __p->parent;
    }
}


/* Compare 2 iterator. */
template <bool k1,bool k2>
bool operator == (const iterator_base <k1> &lhs,
                  const iterator_base <k2> &rhs)
noexcept { return lhs.base() == rhs.base(); }


/* Compare 2 iterator. */
template <bool k1,bool k2>
bool operator != (const iterator_base <k1> &lhs,
                  const iterator_base <k2> &rhs)
noexcept { return lhs.base() != rhs.base(); }


/**
 * @brief Rotate current node with its father.
 * Note that father can't be node on tree.
 * 
 * @param __p Pointer to current node.
 * @param dir It must equal __p->dir()
 */
void rotate(baseptr __p,bool dir) {
    baseptr fa = __p->parent;
    baseptr pa =  fa->parent;

    fa->son[dir]   = __p->son[!dir];
    __p->son[!dir] = fa;
    if(fa->son[dir]) fa->son[dir]->parent = fa;

    fa ->parent = __p;
    __p->parent = pa ;
    if(pa->parent == fa) { /* Father is root. */
        pa->parent = __p;
    } else { /* Father is not root , normal case.  */
        pa->son[pa->son[0] != fa] = __p;
    }
}


/**
 * @brief Rotate current node with its father.
 * 
 * @param __p Pointer to current node.
 */
inline void rotate(baseptr __p) { return rotate(__p,__p->dir()); }

/**
 * @brief Exchange the relative position of current
 * node and next node. Both of which shouldn't be header.
 * Note that __p must have exactly 2 non-null sons.
 * 
 * @param __p Pointer to current node.
 */
void swap_next(baseptr __p) {
    baseptr __n = __p; /* Pointer to next node. */
    advance <1> (__n);

    __p->son[0]->parent = __n;
    __n->son[0] = __p->son[0];
    __p->son[0] = nullptr; /* Manually unfold std::swap. */

    __p->son[1]->parent = __n; /* If __p->son[1] == __n , it still works! */
    if(__n->son[1]) __n->son[1]->parent = __p;
    std::swap(__n->son[1],__p->son[1]);

    if(is_root(__p)) __p->parent->parent = __n;
    else    __p->parent->son[__p->dir()] = __n; 
    std::swap(__n->parent,__p->parent);

    std::swap(__n->color,__p->color);
}

/* Special case when __p and its parent are both red.  */
void insert_fix(baseptr __p) {
    /* Now parent is white , so parent can't be root.  */
    __p->parent->parent->color = Color::WHITE;

    bool dir1 = __p->dir() , dir2 = __p->parent->dir();
    if(dir1 != dir2) {
        __p->color = Color::BLACK;
        rotate(__p,dir1);
        rotate(__p,dir2);
    } else {
        __p->parent->color = Color::BLACK;
        rotate(__p->parent,dir2);
    }
}

/* Balance the node color after inserting a new node. */
void insert_balance(baseptr __p) {
    while(!tree::is_root(__p) && __p->parent->color == Color::WHITE) {
        /* Because parent is white , parent can't be root.  */
        baseptr uncle = __p->parent->bro();
        if(uncle->color != Color::WHITE) break;
        uncle->color = __p->parent->color  = Color::BLACK;
        (__p = __p->parent->parent)->color = Color::WHITE;
    }

    if(is_root(__p)) return (void) (__p->color = Color::BLACK);
    if(__p->parent->color == Color::WHITE) insert_fix(__p);
}

void erase_fix(baseptr __p) {


}

/* Replace current node another node in erasion. */
inline void erase_replace(baseptr __p,baseptr __n) {
    if(is_root(__p)) __p->parent->parent = __n;
    else    __p->parent->son[__p->dir()] = __n;
    __n->color  = Color::BLACK;
    __n->parent = __p->parent;
}


/* Clear the branch containing current node. */
inline void erase_branch(baseptr __p) {
    if(is_root(__p)) __p->parent->parent = __p->parent;
    else    __p->parent->son[__p->dir()] = nullptr;
}

/* Erase black leaf node. */
void erase_leaf(baseptr __p) {
    baseptr fa = __p->parent;
    if(fa->parent == __p) {
        fa->son[0] = fa->son[1] = fa->parent = fa;
        return;
    }

    bool   dir = (__p != fa->son[0]);
    baseptr un = fa->son[!dir];
    fa->son[dir] = nullptr;

    if(!un->son[0] && !un->son[1]) {
        if(fa->color == Color::BLACK) return erase_fix(__p);
        else {
            fa->color = Color::BLACK;
            un->color = Color::WHITE;
            return;
        }
    }

}

/**
 * @brief Erase at given node. No memory is touched.
 * Deconstruction and deallocation function should be 
 * called after this function by user.
 * 
 * @param __p Pointer to target node.
 */
void erase_at(baseptr __p) {
    if(__p->son[0] && __p->son[1]) swap_next(__p);
    /* Now __p has at most 1 son. */

    if(__p->color == Color::WHITE) return erase_branch(__p);
    
    if(__p->son[1]) return erase_replace(__p,__p->son[1]);
    if(__p->son[0]) return erase_replace(__p,__p->son[0]);

    return erase_leaf(__p);
}

}

using key_t   = int;
using T       = long long;
using Compare = std::less <key_t>;

class map {
  public:

    struct implement;
    struct iterator;
    struct const_iterator;

    using value_t   = std::pair <key_t,T>;
    using return_t  = std::pair <iterator,bool>;

    using node      = tree::node <value_t>;
    using pointer   = tree::node <value_t> *;
    using baseptr   = tree::node_base *;
    using node_base = tree::node_base;

  private:

    struct implement : std::allocator <node> , Compare {  
        size_t count;

        template <class ...Args>
        pointer alloc(Args &&...objs) {
            ++count;
            pointer __p = this->allocate(1);
            this->construct(__p,std::forward <Args> (objs)...);
            return __p;
        }

        void dealloc(pointer __p) {
            --count;
            this->destroy(__p);
            this->deallocate(__p,1);
        }

    };

    struct iterator : public tree::iterator_base <0> {
        iterator(baseptr __p = nullptr) noexcept : iterator_base(__p) {}
        value_t &operator * (void) const { return  pointer(ptr)->data; }
        value_t *operator ->(void) const { return &pointer(ptr)->data; }
    };

    struct const_iterator : public tree::iterator_base <1> {
        const_iterator(baseptr __p = nullptr) noexcept : iterator_base(__p) {}
        const value_t &operator * (void) const { return  pointer(ptr)->data; }
        const value_t *operator ->(void) const { return &pointer(ptr)->data; }
    };

    implement impl;
    node_base header; /* Parent as root node || son[0] as largest || son[1] as smallest. */

    baseptr root() const noexcept { return header.parent; }

    /* Special case : insert at root node. */
    return_t insert_root(const value_t &__v) {
        baseptr temp  = impl.alloc(__v);
        header.parent = header.son[0] = header.son[1] = temp;
        temp->parent  = &header;
        temp->color   = tree::Color::BLACK;
        return {temp,true};
    }

  public:

    bool empty()  const noexcept { return !size(); }
    size_t size() const noexcept { return impl.count; }

    /**
     * @brief Insert a key-value pair to the map.
     * If there exists indentical key, insertion will fail.
     * 
     * @param __v The key_value pair to be inserted.
     * @return A pair of iterator of the element and boolean of
     * whether the insertion has been successful.
     */
    return_t insert(const value_t &__v) {
        if(empty()) return insert_root(__v);
        baseptr __p = root() , last = &header;
        bool flag1 = true , flag2 = true;
        while(__p) {
            last = __p;
            if(impl (__v.first,pointer(__p)->data.first) )
                __p = __p->son[0] , flag1 = false;
            else if(impl (pointer(__p)->data.first,__v.first) )
                __p = __p->son[1] , flag2 = false;
            else return {__p,false};
        }

        __p = last->son[__p->dir()] = impl.alloc(__v);
        __p->parent = last;

        if(flag1) header.son[0] = __p; // Maximum
        if(flag2) header.son[1] = __p; // Minimum

        tree::insert_balance(__p);
        return {__p,true};
    }


    size_t erase(const key_t &__k) {
        if(empty()) return 0; // Such node won't exist.
        baseptr __p = root();
        bool flag1 = true , flag2 = true;
        while(__p) {
            if(impl (__k,pointer(__p)->data.first) )
                __p = __p->son[0] , flag1 = false;
            else if(impl (pointer(__p)->data.first,__k) )
                __p = __p->son[1] , flag2 = false;
            else {
                if(flag1 && !__p->son[1]) 
                    header.son[0] = (--iterator(__p)).base();
                if(flag2 && !__p->son[0])
                    header.son[1] = (++iterator(__p)).base();
                tree::erase_at(__p);
                impl.dealloc((pointer)__p);
                return 1;
            }
        }
        return 0;
    }



  public:
    /* Iterator Part. */

    iterator begin() { return header.son[1]; }
    iterator end()   { return   &header;     }


};

constexpr size_t csize = sizeof(map);




}


#endif
