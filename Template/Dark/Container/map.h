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

/* BW_Tree node base */
struct node_base {
    Color  color;
    node_base * parent;
    node_base * son[2];

    inline bool dir() { return this != parent->son[0]; }

    inline node_base *bro() { return this->parent->son[!dir()]; }

    node_base() noexcept :
        color(Color::WHITE),parent(this),son({nullptr,nullptr}) {}
};

using baseptr = node_base *;

inline bool is_root(const node_base *__p) noexcept;
template <bool __d>
inline bool is_dir (const node_base *__p) noexcept;


/* BW_Tree node for  of given value_t(pair <key_t,T>). */
template <class value_t>
struct node : public node_base {
    value_t data;
    node() noexcept = default;
    node(value_t &&__d) noexcept : data(std::move(__d)) {}
    node(const value_t &__d)     : data(__d)            {}
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

    template <bool dir>
    void advance() {
        if(!ptr) throw 114514; /* Error ? */
        if(ptr->son[dir]) {
            ptr = ptr->son[dir];
            while(ptr->son[!dir]) ptr = ptr->son[!dir];
        } else {
            while(is_dir <dir> (ptr)) ptr = ptr->parent;
            ptr = ptr->parent;
        }
    }

    iterator_base &operator ++()
    { advance <1> (); return *this; }

    iterator_base &operator --() 
    { advance <0> (); return *this; }

    iterator_base operator ++(int) noexcept {
        iterator_base temp = *this;
        advance <1> ();
        return temp;
    }

    iterator_base operator --(int) noexcept {
        iterator_base temp = *this;
        advance <0> ();
        return temp;
    }

    baseptr base() const { return ptr; }

};


}


/* Function part. */
namespace tree {


/* Whether the node is root node or header node. */
inline bool is_root(const node_base *__p) noexcept 
{ return __p->parent->parent != __p; }


/**
 * @brief Whether the node is in the given branch of its parent.
 * Note that if current node is root , it returns false.
 * 
 * @tparam __d The target direction of the node.
 * @param __p Pointer to current node.
 * @return || 0 if root or on different branch || 1 otherwise ||
 */
template <bool __d>
inline bool is_dir(const node_base *__p) noexcept
{ return !is_root(__p) && __p->dir() == __d; }


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
 * 
 * @param __p Pointer to urrent node.
 * @param dir It must equal __p->dir()
 * @return || 0 if root remains unchanged || 1 if root requires an update ||
 */
bool rotate(baseptr __p,bool dir) {
    baseptr fa = __p->parent;
    baseptr pa =  fa->parent;
    fa->son[dir]   = __p->son[!dir];
    __p->son[!dir] = fa;
    fa->parent     = __p;
    __p->parent    = pa;
    if(pa->parent == fa) { /* Father is root. */
        pa->parent = __p;
        return true;
    } else { /* Father is not root.  */
        pa->son[pa->son[0] != fa] = __p;
        return false;
    }
}


/**
 * @brief Rotate current node with its father.
 * 
 * @param __p Pointer to urrent node.
 * @return || 0 if root remains unchanged || 1 if root requires an update ||
 */
inline bool rotate(baseptr __p) { return rotate(__p,__p->dir()); }


/**
 * @brief Rebalance the tree after inserting a new node.
 * 
 * @param __p The node inserted.
 * @return || 0 if the root should be updated || 1 nothing else should be done ||
 */
bool insert_balance(baseptr __p) {
    while(!tree::is_root(__p) && __p->parent->color == Color::WHITE) {
        /* Because parent is white , parent can't be root.  */
        baseptr uncle = __p->parent->bro();
        if(uncle->color != Color::WHITE) break;
        uncle->color = __p->parent->color  = Color::BLACK;
        (__p = __p->parent->parent)->color = Color::WHITE;
    }

    if(is_root(__p)) {
        __p->color = Color::BLACK;
        return false; /* No need to update root now. */
    }

    if(__p->parent->color == Color::BLACK) return false;
    /* Now parent is white , so parent can't be root.  */
    __p->parent->parent->color = Color::WHITE;
    bool dir1 = __p->dir() , dir2 = __p->parent->dir();
    if(dir1 != dir2) {
        __p->color = Color::BLACK;
        rotate(__p,dir1);
        return rotate(__p,dir2);
    } else {
        __p->parent->color = Color::BLACK;
        return rotate(__p->parent,dir2);
    }
}

}

using key_t   = int;
using T = long long;
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

    pointer   root;
    implement impl;
    node_base header;

    /* Update root info by header. */
    void update_root() noexcept {
        root = (pointer)header.parent;
        root->parent = &header;
        // root->color = tree::Color::BLACK;     
    }

  public:

    bool empty()  const noexcept { return !root; }
    size_t size() const noexcept { return impl.count; }

    return_t insert(const value_t &__v) {
        if(!root) {
            header.parent = header.son[0] = header.son[1] 
                          = root = impl.alloc(__v);
            root->parent = &header;
            return {root,true};
        }
        baseptr __p = root , last = &header;
        while(__p) {
            last = __p;
            if(impl(__v.first,pointer(last)->data.first))
                __p = __p->son[0];
            else if(impl(pointer(last)->data.first,__v.first))
                __p = __p->son[1];
            else return {__p,false};
        }
        __p = last->son[__p->dir()] = impl.alloc(__v);
        __p->parent = last;
        if(tree::insert_balance(__p)) update_root();
        return {__p,true};
    }

};





}


#endif
