#ifndef _DARK_MAP_H_
#define _DARK_MAP_H_

#include "allocator.h"

#include <cstddef>
#include <cstdlib>
#include <functional>

namespace dark {


/* BW_Tree_Color */
enum class tree_color : bool { BLACK = 0 , WHITE = 1 };

/* BW_Tree_Node_Base */
struct tree_node_base {
    tree_color       color;
    tree_node_base * parent;
    tree_node_base * son[2];

    inline bool dir() { return this != parent->son[0]; }

    tree_node_base() noexcept :
        color(tree_color::WHITE),parent(this),son({nullptr,nullptr}) {}
};

/* BW_Tree_Node_Base */
template <class value_t>
struct tree_node : public tree_node_base {
    value_t data;
    tree_node() noexcept = default;
    tree_node(value_t &&__d) : data(__d) {}
    tree_node(const value_t &__d) noexcept : data(__d) {}

};

using key_t   = int;
using T = long long;
using Compare = std::less <key_t>;

class map {
  public:

    struct implement;
    template <bool is_const>
    class iterator_base;

    using value_t = std::pair <key_t,T>;
    using node    = tree_node <value_t>;
    using Color   = tree_color;
    using pointer = node *;
    using baseptr = tree_node_base *;
    using iterator       = iterator_base <0>;
    using const_iterator = iterator_base <1>;

    using return_t = std::pair <iterator,bool>;

  private:
    

    template <bool is_const>
    class iterator_base {
      private:
        friend class map;
        using U = std::conditional_t <is_const,const node,node>;
        using pointer = U *;
        pointer ptr;

        /* Whether the node is root node or header node. */
        inline static bool is_root(pointer __p) noexcept 
        { return __p->parent->parent != __p; }

        /* Whether the node is on certain direction of father.
           If node is root or header , it returns false.   */
        template <bool __d>
        inline static bool is_dir(pointer __p) noexcept
        { return !is_root(__p) && __p->dir() == __d; }

      public:
        iterator_base(pointer __p) noexcept : ptr(__p) {}

        iterator_base(const iterator_base &rhs) noexcept = default;
        iterator_base(const iterator_base <false> &rhs) noexcept : ptr(rhs.ptr) {}

        template <bool dir>
        void advance() {
            if(!ptr) throw 114514; /* Error ? */
            if(ptr->son[dir]) {
                ptr = ptr->son[dir];
                while(ptr->son[!dir]) ptr ->son[!dir];
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

        U &operator * (void) const { return  ptr->data; }
        U *operator ->(void) const { return &ptr->data; }
    };

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

    pointer   root;
    implement impl;
    tree_node_base header;


  public:

    template <bool k1,bool k2>
    friend bool operator == (const iterator_base <k1> &lhs,
                             const iterator_base <k2> &rhs) 
    noexcept { return lhs.ptr == rhs.ptr; }
    template <bool k1,bool k2>
    friend bool operator != (const iterator_base <k1> &lhs,
                             const iterator_base <k2> &rhs) 
    noexcept { return lhs.ptr != rhs.ptr; }


    baseptr rotate(baseptr __p) {
        baseptr fa = __p->parent;
        baseptr pa =  fa->parent;
        bool dir = __p->dir();
        fa->son[dir]   = __p->son[!dir];
        __p->son[!dir] = fa;
        fa->parent     = __p;
        return __p->parent = pa;
    }

    return_t insert(const value_t &__v) {
        if(!root) {
            root = impl.alloc(__v);
            root->parent = &header;
            header.parent = root;
            return {root,true};
        }


    }



};





}


#endif
