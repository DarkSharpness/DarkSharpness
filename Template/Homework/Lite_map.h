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

    /* Empty construction. */
	constexpr pair() : first() , second() {}
	pair(pair &&other) = default;
	pair(const pair &other) = default;

    pair(T1 &&x) : first(std::move(x)) , second() {}
    pair(const T1 &x) : first(x) , second() {}

    /* Directly copy. */
	pair(const T1 &x, const T2 &y) : first(x), second(y) {}
    /* Perfect forwarding. */
	template<class U1, class U2>
	pair(U1 &&x, U2 &&y) :
        first(std::forward <U1> (x)), second(std::forward <U2> (y)) {}

    /* Copy content. */
	template<class U1, class U2>
	pair(const pair <U1, U2> &other) : 
        first(other.first), second(other.second) {}
	template<class U1, class U2>
    /* Move content. */
	pair(pair <U1, U2> &&other) : 
        first(std::move(other.first)), second(std::move(other.second)) {}
    ~pair() noexcept = default;

    
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
inline bool is_dir (const node_base *__p) noexcept;
template <bool dir>
void advance(baseptr &__p) noexcept;


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


/**
 * @brief The base for iterator of BW_Tree.
 * 
 * @tparam is_const Whether it's a const iterator. 
 */
template <bool is_const,bool dir>
struct iterator_base {
  protected:
    using U = std::conditional_t <is_const,const node_base,node_base>;
    using baseptr = U *;
    baseptr ptr;

  public:
    /* Force to pass a pointer. */
    iterator_base(baseptr __p) noexcept : ptr(__p) {}

    iterator_base(const iterator_base <false,dir> &rhs) noexcept : ptr(rhs.ptr) {}

    iterator_base & operator = (const iterator_base <false,dir> &rhs) 
    noexcept { ptr = rhs.ptr; return *this; }

    iterator_base &operator ++ () noexcept
    { advance <dir> (ptr); return *this; }

    iterator_base &operator -- () noexcept
    { advance <!dir> (ptr); return *this; }

    iterator_base operator ++ (int) noexcept
    { auto temp = *this; advance <dir> (ptr); return temp; }

    iterator_base operator -- (int) noexcept
    { auto temp = *this; advance <!dir> (ptr); return temp; }

    baseptr base() const { return ptr; }

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


/* Judge whether a node is white safely. */
inline bool is_white(const node_base *__p) noexcept
{ return __p && __p->color == Color::WHITE; }


/* Judge whether a node is black safely. */
inline bool is_black(const node_base *__p) noexcept
{ return !__p || __p->color == Color::BLACK; }


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
template <bool k1,bool k2,bool dir>
bool operator == (const iterator_base <k1,dir> &lhs,
                  const iterator_base <k2,dir> &rhs)
noexcept { return lhs.base() == rhs.base(); }


/* Compare 2 iterator. */
template <bool k1,bool k2,bool dir>
bool operator != (const iterator_base <k1,dir> &lhs,
                  const iterator_base <k2,dir> &rhs)
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
    while(!tree::is_root(__p) && __p->parent->color == Color::WHITE) {
        /* Because parent is white , parent can't be root.  */
        baseptr uncle = __p->parent->bro();
        if(is_black(uncle)) break;
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


    /* __p has no son. */
    if(__p->color == Color::BLACK) erase_fix(__p);

    erase_branch(__p);
}

}

// using key_t   = int;
// using T       = int;
// using Compare = std::less <key_t>;

template <class key_t,
          class T,
          class Compare = std::less <key_t> >
class map {
  public:

    struct implement;
    struct iterator;
    struct const_iterator;
    struct reverse_iterator;
    struct const_reverse_iterator;

    using value_t   = sjtu::pair <key_t,T>;
    using return_t  = sjtu::pair <iterator,bool>;

    using node      = tree::node <value_t>;
    using pointer   = tree::node <value_t> *;
    using node_base = tree::node_base;
    using baseptr   = tree::node_base *;

    using pair_t    = sjtu::pair <const key_t,T>;
    using pairptr   = pair_t *;

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


    struct iterator : public tree::iterator_base <0,1> {
        iterator(baseptr __p = nullptr) noexcept : iterator_base(__p) {}
        pair_t &operator * (void) const { return  cast(pointer(ptr)->data); }
        pair_t *operator ->(void) const { return &cast(pointer(ptr)->data); }
    };

    struct const_iterator : public tree::iterator_base <1,1> {
        const_iterator(baseptr __p = nullptr) noexcept : iterator_base(__p) {}
        const pair_t &operator * (void) const { return  cast(pointer(ptr)->data); }
        const pair_t *operator ->(void) const { return &cast(pointer(ptr)->data); }
    };

    struct reverse_iterator : public tree::iterator_base <0,0> {
        reverse_iterator(baseptr __p = nullptr)
            noexcept : iterator_base(__p) {}
        pair_t &operator * (void) const { return  cast(pointer(ptr)->data); }
        pair_t *operator ->(void) const { return &cast(pointer(ptr)->data); }
    };

    struct const_reverse_iterator : public tree::iterator_base <1,0> {
        const_reverse_iterator(baseptr __p = nullptr)
            noexcept : iterator_base(__p) {}
        const pair_t &operator * (void) const { return  cast(pointer(ptr)->data); }
        const pair_t *operator ->(void) const { return &cast(pointer(ptr)->data); }
    };

  private:

    implement impl;   /* Implement of compare and memory function. */
    node_base header; /* Parent as root node || son[0] as largest || son[1] as smallest. */

    baseptr root() const noexcept { return header.parent; }

    /* Cast value_t to pair_t */
    static inline pair_t & cast(value_t &__v) 
    {  return reinterpret_cast <pair_t &> (__v) ;}


    /* Special case : insert at root node. */
    return_t insert_root(baseptr __n) {
        ++impl.count;
        header.parent = header.son[0] = header.son[1] = __n;
        __n->parent   = &header;
        __n->color    = tree::Color::BLACK;
        return {__n,true};
    }

    /* Clean subtree info without modifying tree size. */
    void clean(baseptr __p) {
        if(!__p) return;
        clean(__p->son[0]);
        clean(__p->son[1]);
        impl.dealloc(__p);
    }

    /* Debug use only!!! */
    int check(baseptr __p,tree::Color C) {
        if(!__p) return 0;
        if(__p->color == tree::Color::WHITE && __p->color == C) throw "Double red!";
        int t = check(__p->son[0],__p->color);
        if(t != check(__p->son[1],__p->color)) throw "Different length!";
        return t + (__p->color == tree::Color::BLACK);
    }

    /* Copy sub_tree information. */
    pointer copy(pointer __p) {
        if(!__p) return nullptr;
        pointer __c = impl.alloc(__p->data); /* Current node. */  
        __c->son[0] = copy((pointer)__p->son[0]);
        if(__c->son[0]) __c->son[0]->parent = __c;
        __c->son[1] = copy((pointer)__p->son[1]);
        if(__c->son[1]) __c->son[1]->parent = __c;
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

    // /**
    //  * @brief Advance the pointer to target location.
    //  * 
    //  * @param __p Pointer to advance to target location.
    //  * @param __k Key to locate.
    //  * @return || -1 if exactly the node || 0 / 1 as direction.
    //  */
    // inline int insert_locate(baseptr &__p,const key_t &__k) {
    //     while(true) {
    //         if(impl (__k,pointer(__p)->data.first) ) {
    //             if(__p->son[0]) __p = __p->son[0];
    //             else return 0;
    //         }
    //         else if(impl (pointer(__p)->data.first,__k) )
    //             if(__p->son[1]) __p = __p->son[1];
    //             else return 1;
    //         else return -1;
    //     }
    // }

    /**
     * @brief Insert a key-value pair into the map.
     * If __key
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

        /* Avoid misusage. */
        static_assert (std::is_same_v <std::decay_t <key_t>,
                                       std::decay_t <U>   >,"Misusage");

        if(empty()) /* Just empty , so insert at root node. */
            return insert_root(impl.alloc(std::forward <U> (__k),
                                          std::forward <V> (__v)...));

        baseptr __p = header.parent;

        // int dir = insert_locate(__p,__v.first);
        // if(dir < 0) return {__p,false};

        bool dir;
        while(true) {
            if(impl (__k,pointer(__p)->data.first) ) {
                if(__p->son[0]) __p = __p->son[0];
                else {dir = 0;break;}
            }
            else if(impl (pointer(__p)->data.first,__k) )
                if(__p->son[1]) __p = __p->son[1];
                else {dir = 1;break;}
            else return {__p,false};
        }

        ++impl.count;
        __p->son[dir] = impl.alloc(std::forward <U> (__k),
                                   std::forward <V> (__v)...);
        __p->son[dir]->parent = __p;

        if(__p == header.son[!dir]) header.son[!dir] = __p->son[dir];

        tree::insert_at(__p = __p->son[dir]);
        return {__p,true};
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
     * @return Reference to the value. 
     * @throw sjtu::index_out_of_bound() if __k not in map.
     */
    T & access(const key_t & __k) const {
        baseptr iter = locate(__k);
        if(!iter) throw sjtu::index_out_of_bound();
        else return pointer(iter)->data.second;
    }

  public:
    /* Initialize from empty. */
    map() noexcept : impl(),header(&header) {}

    /* Initialize by copying another map. */
    map(const map &rhs) noexcept : impl(rhs.impl),header(&header) {
        if(rhs.empty()) return;
        header.parent = copy((pointer)rhs.root());

        baseptr __p; /* Find out the smallest and largest node. */

        __p = root();
        while(__p->son[0]) __p = __p->son[0];
        header.son[1] = __p;

        __p = root();
        while(__p->son[1]) __p = __p->son[1];
        header.son[0] = __p;
    }

    /* Initialize by moving another map.  */
    map(map &&rhs) noexcept : impl(std::move(rhs.impl)),header(&header) {
        if(rhs.empty()) return;
        header = rhs.header;
        /* Clean the data of rhs map. */
        rhs.impl.count = 0;
        rhs.header.son[0] = rhs.header.son[1] 
                          = rhs.header.parent = &rhs.header;
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
    return_t insert(const value_t &__v) { return insert_pair(__v.first,
                                                             __v.second); }
    /**
     * @brief Insert a key-value pair to the map.
     * If there exists indentical key, insertion will fail.
     *
     * @param __v Key-value pair to be inserted.
     * @return A pair of an iterator of the element and
     * a boolean of whether the insertion has been successful.
     */
    return_t insert(value_t &&__v) { return insert_pair(std::move(__v.first),
                                                        std::move(__v.second)); }

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
     * @param __i Non-const (reverse) iterator to a key-value pair.
     * @return Count of key-value pairs erased. (0 or 1)
     */
    template <bool dir>
    size_t erase(tree::iterator_base <0,dir> __i) {
        if(is_header(__i.base())) return 0;
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
        else        return {__p};
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
        else        return {__p};
    }

    /* Return counts of node with given key. (0 or 1) */
    size_t count(const key_t &__k) const noexcept 
    { return locate(__k) != nullptr; }

    /* Clear the memory storage. */
    void clear() noexcept { if(impl.count) { clean(root()) , impl.count = 0; } }

    T &operator [] (const key_t &__k) { return insert_pair(__k).first->second; }

    const T &operator [] (const key_t &__k) const { return access(__k); }

    T &at(const key_t &__k) { return access(__k); }

    const T &at (const key_t &__k) const { return access(__k); }

    void check() { check(root(),tree::Color::WHITE); }

  public:
    /* Iterator Part. */

    iterator begin() noexcept { return header.son[1]; }
    iterator end()   noexcept { return   &header;     }

    const_iterator begin() const noexcept  { return header.son[1]; }
    const_iterator end()   const noexcept  { return   &header;     }
    const_iterator cbegin() const noexcept { return header.son[1]; }
    const_iterator cend()   const noexcept { return   &header;     }

    reverse_iterator rbegin() { return header.son[0]; }
    reverse_iterator rend()   { return   &header;     }
    const_reverse_iterator rbegin() const noexcept  { return header.son[0]; }
    const_reverse_iterator rend()   const noexcept  { return   &header;     }
    const_reverse_iterator crbegin() const noexcept { return header.son[0]; }
    const_reverse_iterator crend()   const noexcept { return   &header;     }
};



}


#endif
