// For a better version,see https://github.com/DarkSharpness/DarkSharpness/blob/main/Template/Dark/Container/map.h
#ifndef _DARK_MAP_H_
#define _DARK_MAP_H_


// #include "utility.hpp"

#include "exceptions.hpp"
#include <cstddef>
#include <cstdlib>
#include <functional>

namespace sjtu {

template<class T1, class T2>
class pair {
  public:
	T1 first;
	T2 second;

	constexpr pair() : first(), second() {}
	pair(const pair &other) = default;
	pair(pair &&other) = default;

    pair(T1 &&x) : first(std::move(x)) {}

    pair(const T1 &x) : first(x) {}
	pair(const T1 &x, const T2 &y) : first(x), second(y) {}

	template<class U1, class U2>
	pair(U1 &&x, U2 &&y) : first(std::move(x)), second(std::move(y)) {}

	template<class U1, class U2>
	pair(const pair<U1, U2> &other) : first(other.first), second(other.second) {}

	template<class U1, class U2>
	pair(pair<U1, U2> &&other) : first (std::move(other.first)),
                                 second(std::move(other.second)) {}
};

}


namespace dark {

/* Struct part. */
namespace tree {


/* BW_Tree color */
enum struct Color : bool { BLACK = 0 , WHITE = 1 };


struct node_base;
using baseptr = node_base *;


inline bool is_root(const node_base *__p) noexcept;

template <bool dir>
[[deprecated]] inline bool is_dir (const node_base *__p) noexcept;

template <bool dir>
void advance(baseptr &__p) noexcept;

template <bool dir>
void advance(const node_base *&__p) noexcept;

void check(const node_base *__p);

/* BW_Tree node base */
struct node_base {
    Color   color;
    baseptr parent;
    baseptr son[2];

    /* Return the direction of this branch. */
    inline bool dir() const noexcept { return this != parent->son[0]; }
 
    /* Whether this is on the __d branch of parent.  */
    inline bool dir(bool __d) const noexcept { return this == parent->son[__d]; }

    /* Return the brother node. It requires existence of parent node. */
    inline baseptr bro() const noexcept { return this->parent->son[dir(0)]; }

    /* Initialize by setting to null or given pointer. */
    node_base(baseptr __p = nullptr) noexcept
        : color(Color::WHITE),parent(__p) { son[0] = son[1] = __p; }
};

/* BW_Tree node for given value_t(pair <key_t,T>). */
template <class value_t>
struct node : public node_base {
    value_t data;
    node() noexcept = default;

    node(value_t  &__d)          : data(__d)            {}
    node(const value_t &__d)     : data(__d)            {}
    node(value_t &&__d) noexcept : data(std::move(__d)) {}
    node(const value_t &&__d) noexcept : data(__d)      {}

    template <class ...Args>
    node(Args &&...objs) noexcept : data(std::forward <Args> (objs)...) {} 

};


/**
 * @brief The base for iterator of BW_Tree.
 * 
 * @tparam is_const Whether it's a const iterator. 
 */
template <class value_t,bool is_const,bool dir>
struct iterator_base {
  protected:
    using U = std::conditional_t <is_const,const node_base,node_base>;
    using V = std::conditional_t <is_const,const node <value_t>,node <value_t>>;

  public:
    /* iterator_trait */
    using iterator_assignable = std::integral_constant <bool,is_const>;
    using iterator_category   = std::bidirectional_iterator_tag;
    using value_type = value_t;
    using reference  = value_t &;
    using pointer    = U *;
 
  protected:
    /* Data part */
    pointer     ptr; /* Data pointer */
    const void *map; /* Map  pointer */

  public:

    /* Force to pass a pointer. */
    iterator_base(pointer __p = nullptr,const void *__m = nullptr) 
    noexcept : ptr(__p),map(__m) {}

    /* Const one construct from non-const one. */
    iterator_base(const iterator_base <value_t,false,dir> &rhs) 
    noexcept : ptr(rhs.base()),map(rhs.source()) {}

    iterator_base &operator ++ ()
    { check(ptr); advance <dir> (ptr); return *this; }

    iterator_base &operator -- ()
    { advance <!dir> (ptr); check(ptr); return *this; }

    iterator_base operator ++ (int)
    { auto temp = *this; operator++(); return temp; }

    iterator_base operator -- (int)
    { auto temp = *this; operator--(); return temp; }

    auto &operator * (void) const { return  ((V *)(ptr))->data; }
    auto *operator ->(void) const { return &((V *)(ptr))->data; }

    pointer base()       const { return ptr; }
    const void *source() const { return map; }
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
[[deprecated]] inline bool is_dir(const node_base *__p) noexcept
{ return !is_root(__p) && __p->dir(dir); }


/* Judge whether a node is white safely. */
inline bool is_white(const node_base *__p) noexcept
{ return __p && __p->color == Color::WHITE; }


/* Judge whether a node is black safely. */
[[deprecated]] inline bool is_black(const node_base *__p) noexcept
{ return !__p || __p->color == Color::BLACK; }


/**
 * @brief Advance toward target direcition by one step.
 * 
 * @tparam dir Target direction.
 * @param __p The pointer to advance.
 */
template <bool dir>
void advance(baseptr &__p) noexcept { 
    if(!__p) return ; /* Error ? */

    if(__p->son[dir]) { /* Downward */
        if(__p == __p->son[dir]) return;
        __p = __p->son[dir];
        while(__p->son[!dir]) __p = __p->son[!dir];
    } else { /* Upward. */
        baseptr __f = __p->parent;
        while(__f->parent != __p && __f->son[dir] == __p)
        { __p = __f ; __f = __p->parent; }
        __p = __f;
    }
}


/**
 * @brief Advance toward target direcition by one step.
 * 
 * @tparam dir Target direction.
 * @param __p The pointer to advance.
 */
template <bool dir>
void advance(const node_base *&__p) noexcept { 
    if(!__p) return ; /* Error ? */

    if(__p->son[dir]) { /* Downward */
        if(__p == __p->son[dir]) return;
        __p = __p->son[dir];
        while(__p->son[!dir]) __p = __p->son[!dir];
    } else { /* Upward. */
        baseptr __f = __p->parent;
        while(__f->parent != __p && __f->son[dir] == __p)
        { __p = __f ; __f = __p->parent; }
        __p = __f;
    }
}


/* Compare 2 iterator. */
template <class T,bool k1,bool k2,bool dir>
bool operator == (const iterator_base <T,k1,dir> &lhs,
                  const iterator_base <T,k2,dir> &rhs)
noexcept { return lhs.base() == rhs.base(); }


/* Compare 2 iterator. */
template <class T,bool k1,bool k2,bool dir>
bool operator != (const iterator_base <T,k1,dir> &lhs,
                  const iterator_base <T,k2,dir> &rhs)
noexcept { return lhs.base() != rhs.base(); }


/**
 * @brief Rotate current node with its father.
 * Note that father can't be node on tree.
 * 
 * @param __p Pointer to current node.
 * @param dir It must equal __p->dir()
 */
void rotate(baseptr __p,bool dir) {
    baseptr __f = __p->parent; /* Father */
    baseptr __g = __f->parent; /* Grand-father */

    __f->son[dir]  = __p->son[!dir];
    __p->son[!dir] = __f;
    if(__f->son[dir]) __f->son[dir]->parent = __f;

    __f->parent = __p;
    __p->parent = __g;
    if(__g->parent == __f) { /* Father is root. */
        __g->parent = __p;
    } else { /* Father is not root , normal case.  */
        __g->son[__g->son[0] != __f] = __p;
    }
}


/**
 * @brief Rotate current node with its father.
 * 
 * @param __p Pointer to current node.
 */
inline void rotate(baseptr __p) { return rotate(__p,__p->dir()); }


/**
 * @brief Exchange the relative position of current node
 * and next node. Both of which shouldn't be header node.
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
    if(__n->parent != __n) __n->parent->son[0] = __p;
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


/* Adjust the node color after inserting a new node. */
void insert_at(baseptr __p) {
    while(!is_root(__p) && __p->parent->color == Color::WHITE) {
        /* Because parent is white , parent can't be root.  */
        baseptr uncle = __p->parent->bro();
        if(!is_white(uncle)) break;
        uncle->color = __p->parent->color  = Color::BLACK;
        (__p = __p->parent->parent)->color = Color::WHITE;
    }

    if(is_root(__p)) return (void) (__p->color = Color::BLACK);
    if(__p->parent->color == Color::WHITE) insert_fix(__p);
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


/* Fix black leaf case. */
void erase_fix(baseptr __p) {
    while(true) { /* __p side is shorter in black length by 1.  */
        baseptr __f = __p->parent; /* Father node. */

        /* __p is root node , so do nothing now. */
        if(__f->parent == __p) break;

        bool dir = (__f->son[0] != __p); /* Direction of __p. */
        baseptr __b = __f->son[!dir];    /* Brother node. */

        if(__b->color == Color::WHITE) { /* Transform case. */
            rotate(__b,!dir);
            __f->color = Color::WHITE;
            __b->color = Color::BLACK;
            __b = __f->son[!dir]; /* Update brother node. */
        }

        /* Now __b is black. */

        /* Not in a line case. */
        if(is_white(__b->son[dir])) { 
            rotate(__b->son[dir],dir);
            __b->color = Color::WHITE;
            __b = __b->parent; /* Update to __f->son[!dir] */
            __b->color = Color::BLACK;
        }

        /* In a line case. */
        if(is_white(__b->son[!dir])) {
            rotate(__b,!dir); /* Now __b is the root. */
            __b->color = __f->color; /* Father color not changed. */
            __f->color = __b->son[!dir]->color = Color::BLACK;
            break;
        }

        /* Now __b has no son. */

        if(__f->color == Color::WHITE) {
            __f->color = Color::BLACK;
            __b->color = Color::WHITE;
            break;
        }

        /* Double black case require looping. */

        __b->color = Color::WHITE;
        __p = __f;
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

    /* __p has one son, so the son must be red. */
    if(__p->son[1]) return erase_replace(__p,__p->son[1]); 
    /* This case is slightly less likely to happen due to swap_next. */
    if(__p->son[0]) return erase_replace(__p,__p->son[0]);

    /* Now __p has no son. */
    if(__p->color == Color::BLACK) erase_fix(__p);

    erase_branch(__p);
}

void check(const node_base *__p) { 
    if(!__p || is_header(__p)) throw sjtu::index_out_of_bound(); 
}

}


}


namespace dark {

using key_t = long long;
using T = double;
using Compare = std::less <key_t>;

template <class key_t,
          class T,
          class Compare = std::less <key_t> >
class map {
  private:
    struct implement;

    using value_t   = sjtu::pair <const key_t,T>;
    using node      = tree::node <value_t>;
    using pointer   = tree::node <value_t> *;
    using node_base = tree::node_base;
    using baseptr   = tree::node_base *;

  public:

    using iterator       = tree::iterator_base <value_t,0,1>;
    using const_iterator = tree::iterator_base <value_t,1,1>;
    using return_t       = sjtu::pair <iterator,bool>;
    using value_type     = value_t;
    
  private:

    struct implement : std::allocator <node> , Compare {  
        size_t count;

        implement() noexcept : count(0) {}

        template <class ...Args>
        pointer alloc(Args &&...objs) {
            pointer __p = this->allocate(1);
            this->construct(__p,std::forward <Args> (objs)...);
            return __p;
        }

        void dealloc(baseptr __p) {
            this->destroy((pointer)__p);
            this->deallocate((pointer)__p,1);
        }

    };

    implement impl;   /* Implement of compare and memory function. */
    node_base header; /* Parent as root node || son[0] as largest || son[1] as smallest. */

    /* Return the root node of the tree. */
    baseptr root() const noexcept { return header.parent; }

    /* Special case : insert at root node. */
    return_t insert_root(baseptr __n) {
        ++impl.count;
        header.parent = header.son[0] = header.son[1] = __n;
        __n->parent   = &header;
        __n->color    = tree::Color::BLACK;
        return {{__n,this},true};
    }

    /* Clean subtree info without modifying tree size. */
    void clean(baseptr __p) {
        if(!__p) return;
        clean(__p->son[0]);
        clean(__p->son[1]);
        impl.dealloc(__p);
    }

    /* Copy sub_tree information. Note that __p can't be null! */
    pointer copy(pointer __p) {
        pointer __c = impl.alloc(__p->data); /* Current node. */
        __c->color  = __p->color;
        if(__p->son[0]) {
            __c->son[0] = copy((pointer)__p->son[0]);
            __c->son[0]->parent = __c;
        }
        if(__p->son[1]) {
            __c->son[1] = copy((pointer)__p->son[1]);
            __c->son[1]->parent = __c;
        }
        return __c;
    }

    /**
     * @brief Tries to locate a node with given key.
     * Note that the tree mustn't be empty.
     * 
     * @param __k Key to locate.
     * @return Pointer to node with given key.
     * If not existing , return nullptr.
     */
    baseptr locate(const key_t &__k) const noexcept {
        if(empty()) return nullptr;
        baseptr __p = root();
        while(__p) {
            if(impl (__k,pointer(__p)->data.first) )
                __p = __p->son[0];
            else if(impl (pointer(__p)->data.first,__k) )
                __p = __p->son[1];
            else break;
        }
        return __p;
    }

    /**
     * @brief Insert a key-value pair into the map.
     * 
     * @param __n Pointer to new memory block or nullptr.
     * @param __v Key-value to be inserted.
     * @return return_t A pair of an iterator of the element and
     * a boolean of whether the insertion has been successful.
     */
    template <class U,class ...V>
    return_t insert_pair(U &&__k,V &&...__v) {
        /* 
            In fact, this function was intended to support std::piecewise construct.
            However,it turned out that this is too much for me.
            I'm fed up . So you see such a function as below , like a piece of SHIT.
        */

        if(empty()) /* Just empty , so insert at root node. */
            return insert_root( impl.alloc(std::forward <U> (__k),
                                           std::forward <V> (__v)...) );

        baseptr __p = root();
        bool dir;
        while(true) {
            if(impl (__k,pointer(__p)->data.first) ) {
                if(__p->son[0]) __p = __p->son[0];
                else { dir = 0; break; }
            } else if(impl (pointer(__p)->data.first,__k) )
                if(__p->son[1]) __p = __p->son[1];
                else { dir = 1 ;break; }
            else return {__p,false};
        }

        ++impl.count;
        __p->son[dir] = impl.alloc(std::forward <U> (__k),
                                   std::forward <V> (__v)...);
        __p->son[dir]->parent = __p;

        /* May update the largest / smallest. */
        if(__p == header.son[!dir]) header.son[!dir] = __p->son[dir];

        tree::insert_at(__p = __p->son[dir]);
        return {{__p,this},true};
    }

    /**
     * @brief Inner function to erase given node.
     * 
     * @param __p Pointer to given node.
     * @return Always be 1.
     */
    size_t erase_pair(baseptr __p) {
        /*  Update largest in constant time. */
        if(__p == header.son[0])
            header.son[0] = __p->son[0] ? __p->son[0] : __p->parent;
        /* Update smallest in constant time. */
        if(__p == header.son[1])
            header.son[1] = __p->son[1] ? __p->son[1] : __p->parent;

        tree::erase_at(__p);
        --impl.count;
        impl.dealloc(__p);
        return 1;
    }

    /**
     * @brief Access the the value tied with given key.
     * 
     * @param __k Key to locate.
     * @return Pointer to the value. If not found throw. 
     */
    T &access(const key_t & __k) const {
        baseptr iter = locate(__k);
        if(!iter) throw sjtu::index_out_of_bound();
        return pointer(iter)->data.second;
    }

    /* Manually initialize the header and count of nodes. */
    void initialize() noexcept { ::new (&header) node_base(&header); impl.count = 0; }

  public:
    /* Initialize from empty. */
    map() noexcept : impl(),header(&header) {}

    /* Initialize by copying another map. */
    map(const map &rhs) : impl(rhs.impl),header(&header) {
        if(rhs.empty()) return;

        header.parent  = copy(pointer(rhs.root()));
        root()->parent = &header;

        /* Find out the smallest and largest node. */
        baseptr __p;

        __p = root(); /* Smallest */
        while(__p->son[0]) __p = __p->son[0];
        header.son[1] = __p;

        __p = root(); /* Largest  */
        while(__p->son[1]) __p = __p->son[1];
        header.son[0] = __p;
    }

    /* Initialize by moving another map.  */
    map(map &&rhs) noexcept : impl(std::move(rhs.impl)),header(&header) {
        if(rhs.empty()) return;

        header = rhs.header;
        root()->parent = &header;

        /* Clean the data of rhs map. */
        rhs.initialize();
    }

    /* Too lazy to overload. */
    map &operator = (const map &rhs) {
        if(this != &rhs) {
            this->~map();
            ::new (this) map(rhs);
        }
        return *this;
    }

    /* Too lazy to overload. */
    map &operator = (map &&rhs) {
        if(this != &rhs) {
            this->~map();
            ::new (this) map(std::move(rhs));
        }
        return *this;
    }

    /* Clean the storage. */
    ~map() noexcept { clear(); }

    /* Return whether the map is empty. */
    bool empty()  const noexcept { return !impl.count; }

    /* Return count of key-value pair in this map. */
    size_t size() const noexcept { return impl.count;  }

    /**
     * @brief Insert a key-value pair to the map.
     * If there exists indentical key, insertion will fail.
     *
     * @param __v Key-value pair to be inserted.
     * @return A pair of an iterator of the element and
     * a boolean of whether the insertion has been successful.
     */
    return_t insert(const value_t &__v) 
    { return insert_pair(__v.first,__v.second); }
    /**
     * @brief Insert a key-value pair to the map.
     * If there exists indentical key, insertion will fail.
     *
     * @param __v Key-value pair to be inserted.
     * @return A pair of an iterator of the element and
     * a boolean of whether the insertion has been successful.
     */
    return_t insert(value_t &&__v) 
    { return insert_pair(std::move(__v.first),std::move(__v.second)); }

    /**
     * @brief Erase all key-value pair with given key from the map.
     * If no such key exists, nothing will be done.
     * 
     * @param __k Key to locate the key-value pair.
     * @return Count of key-value pairs erased. (0 or 1)
     */
    size_t erase(const key_t &__k) {
        baseptr __p = locate(__k);
        if(!__p) return 0;
        else return erase_pair(__p);
    }

    /**
     * @brief Erase one key-value pair with given iterator from the map.
     * 
     * @param __i Non-const iterator to a key-value pair.
     * @return Count of key-value pairs erased. (0 or 1)
     */
    size_t erase(iterator __i) {
        if(__i.source() != this || __i.base() == &header) throw sjtu::runtime_error();
        else return erase_pair(__i.base());
    }

    /**
     * @brief Find a node with given key.
     * 
     * @param __k Key to locate the node.
     * @return Iterator to the node if found,
     * otherwise iterator to end.
     */
    iterator find(const key_t &__k) noexcept {
        baseptr __p = locate(__k);
        if(!__p)    return end();
        else        return {__p,this};
    }

    /**
     * @brief Find a node with given key.
     * 
     * @param __k Key to locate the node.
     * @return Iterator to the node if found,
     * otherwise iterator to end.
     */
    const_iterator find(const key_t &__k) const noexcept {
        baseptr __p = locate(__k);
        if(!__p)    return end();
        else        return {__p,this};
    }

    /* Return counts of node with given key. (0 or 1) */
    size_t count(const key_t &__k) const noexcept 
    { return locate(__k) != nullptr; }

    /* Clear the memory storage. */
    void clear() noexcept {
        if(impl.count) {
            clean(root());
            initialize();
        }
    }

    T &operator [] (key_t &&__k) { return insert_pair(std::move(__k)).first->second; }
    T &operator [] (const key_t &__k) { return insert_pair(__k).first->second; }

    const T &operator [] (const key_t &__k) const { return access(__k); }

    T &at(const key_t &__k) { return access(__k); }

    const T &at(const key_t &__k) const { return access(__k); }

  public:
    /* Iterator Part. */

    iterator begin() noexcept { return {header.son[1],this}; }
    iterator end()   noexcept { return    {&header,this};    }

    const_iterator begin() const noexcept  { return {header.son[1],this}; }
    const_iterator end()   const noexcept  { return   {&header,this};     }
    const_iterator cbegin() const noexcept { return {header.son[1],this}; }
    const_iterator cend()   const noexcept { return   {&header,this};     }

};



}

namespace sjtu {

template <class key_t,class T,class Compare = std::less <key_t>>
using map = dark::map <key_t,T,Compare>;

}

#endif
