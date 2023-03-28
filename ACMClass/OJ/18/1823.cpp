#include <iostream>
// #include <Dark/map>

#ifndef _DARK_TREE_H_
#define _DARK_TREE_H_


namespace dark {

/* Struct part. */
namespace tree {


/* BW_Tree color */
enum struct Color : bool { BLACK = 0 , WHITE = 1 };

struct node_base;

inline bool is_root(const node_base *__p) noexcept;

template <bool dir>
[[deprecated]] inline bool is_dir (const node_base *__p) noexcept;

template <bool dir>
void advance(node_base *&__p) noexcept;

template <bool dir>
void advance(const node_base *&__p) noexcept;


/* BW_Tree node base */
struct node_base {
    using baseptr = node_base *;
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


/* A tag marking perfect forwarding. */
struct forward_tag {};

/* BW_Tree node for given value_t(pair <key_t,T>). */
template <class value_t>
struct node : public node_base {
    value_t data;
    node() = default;

    template <class ...Args>
    node(forward_tag,Args &&...objs) : data(std::forward <Args> (objs)...) {} 

};


/* An implement for node allocator. */
template <class value_t,
          class allocator_t = std::allocator <value_t>,
          class ...Ts>
struct implement : allocator_t , Ts ... {
    using pointer = value_t *;
    size_t count = 0;

    template <class ...Args>
    inline pointer alloc(Args &&...objs) {
        pointer __p = this->allocate(1);
        this->construct(__p,std::forward <Args> (objs)...);
        return __p;
    }

    inline void dealloc(void *__p) {
        this->destroy((pointer)__p);
        this->deallocate((pointer)__p,1);
    }

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

    iterator_base & operator = (const iterator_base <false,dir> &rhs) 
    noexcept { ptr = rhs.ptr; return *this; }

    iterator_base &operator ++ () noexcept
    { advance <dir> (ptr); return *this; }

    iterator_base &operator -- () noexcept
    { advance <!dir> (ptr); return *this; }

    iterator_base operator ++ (int) noexcept
    { auto temp = *this; advance <dir>  (ptr); return temp; }

    iterator_base operator -- (int) noexcept
    { auto temp = *this; advance <!dir> (ptr); return temp; }

    baseptr base() const { return ptr; }

};



template <bool is_const,bool dir>
struct index_iterator : iterator_base <is_const,dir> {
  protected:
    size_t rank;
    using Base    = iterator_base <is_const,dir>;
    using baseptr = typename Base::baseptr;
  public:

    index_iterator(baseptr __p,size_t __n) noexcept : Base(__p),rank(__n) {}

    index_iterator & operator++(void) noexcept
    { ++rank, Base::operator++(); }



    size_t index() const { return rank; }
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
void advance(node_base *&__p) noexcept { 
    if(!__p || __p == __p->son[dir]) return; /* Null or empty case. */

    if(__p->son[dir]) { /* Downward */
        __p = __p->son[dir];
        while(__p->son[!dir]) __p = __p->son[!dir];
    } else { /* Upward. */
        node_base * __f = __p->parent;
        while(__f->parent != __p && __f->son[dir] == __p)
            __f = (__p = __f)->parent;
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
    if(!__p || __p == __p->son[dir]) return; /* Null or empty case. */

    if(__p->son[dir]) { /* Downward */
        __p = __p->son[dir];
        while(__p->son[!dir]) __p = __p->son[!dir];
    } else { /* Upward. */
        const node_base * __f = __p->parent;
        while(__f->parent != __p && __f->son[dir] == __p) 
            __f = (__p = __f)->parent;
        __p = __f;
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

template <bool k1,bool k2,bool dir>
size_t operator - (const index_iterator <k1,dir> &lhs,
                   const index_iterator <k2,dir> &rhs)
noexcept { return lhs.index() - rhs.index(); }



using baseptr = node_base *;

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

}


}


#endif

#ifndef _DARK_MAP_H_
#define _DARK_MAP_H_


#include <cstddef>
#include <cstdlib>

namespace dark {


template <class key_t,
          class T,
          class Compare>
class map {
  public:

    struct iterator;
    struct const_iterator;
    struct reverse_iterator;
    struct const_reverse_iterator;

    using value_t   = std::pair <key_t,T>;
    using return_t  = std::pair <iterator,bool>;
  
  private:

    using node_base = tree::node_base;
    using baseptr   = tree::node_base *;
    using node      = tree::node <value_t>;
    using pointer   = tree::node <value_t> *;
    using pair_t    = std::pair <const key_t,T>;
    using pairptr   = std::pair <const key_t,T> *;

    using implement = tree::implement <node,std::allocator <node>,Compare>;

  public:

    struct iterator : public tree::iterator_base <0,1> {
      protected:
        using Base    = iterator_base;
        using baseptr = typename Base::baseptr; 
      public:

        iterator(baseptr __p = nullptr) noexcept : iterator_base(__p) {}

        iterator & operator ++(void) noexcept
        { Base::operator++(); return *this; }

        iterator & operator --(void) noexcept
        { Base::operator--(); return *this; }

        iterator operator ++ (int) noexcept
        { auto temp = *this; Base::operator++(); return temp; }

        iterator operator -- (int) noexcept
        { auto temp = *this; Base::operator--(); return temp; }

        pair_t &operator * (void) const { return  cast(pointer(ptr)->data); }
        pair_t *operator ->(void) const { return &cast(pointer(ptr)->data); }
    };

    struct const_iterator : public tree::iterator_base <1,1> {
      protected:
        using Base    = iterator_base;
        using baseptr = typename Base::baseptr; 
      public:

        const_iterator(baseptr __p = nullptr) noexcept : iterator_base(__p) {}
        const_iterator(const iterator &rhs) : iterator_base(rhs) {}

        const_iterator & operator ++(void) noexcept
        { Base::operator++(); return *this; }

        const_iterator & operator --(void) noexcept
        { Base::operator--(); return *this; }

        const_iterator operator ++ (int) noexcept
        { auto temp = *this; Base::operator++(); return temp; }

        const_iterator operator -- (int) noexcept
        { auto temp = *this; Base::operator--(); return temp; }

        const pair_t &operator * (void) const { return  cast(pointer(ptr)->data); }
        const pair_t *operator ->(void) const { return &cast(pointer(ptr)->data); }
    };

    struct reverse_iterator : public tree::iterator_base <0,0> {
      protected:
        using Base    = iterator_base;
        using baseptr = typename Base::baseptr; 
      public:

        reverse_iterator(baseptr __p = nullptr)
        noexcept : iterator_base(__p) {}

        reverse_iterator & operator ++(void) noexcept
        { Base::operator++(); return *this; }

        reverse_iterator & operator --(void) noexcept
        { Base::operator--(); return *this; }

        reverse_iterator operator ++ (int) noexcept
        { auto temp = *this; Base::operator++(); return temp; }

        reverse_iterator operator -- (int) noexcept
        { auto temp = *this; Base::operator--(); return temp; }

        pair_t &operator * (void) const { return  cast(pointer(ptr)->data); }
        pair_t *operator ->(void) const { return &cast(pointer(ptr)->data); }
    };

    struct const_reverse_iterator : public tree::iterator_base <1,0> {
      protected:
        using Base    = iterator_base;
        using baseptr = typename Base::baseptr; 
      public:

        const_reverse_iterator(baseptr __p = nullptr)
        noexcept : iterator_base(__p) {}
        const_reverse_iterator(const reverse_iterator &rhs)
        noexcept : iterator_base(rhs) {}

        const_reverse_iterator & operator ++(void) noexcept
        { Base::operator++(); return *this; }

        const_reverse_iterator & operator --(void) noexcept
        { Base::operator--(); return *this; }

        const_reverse_iterator operator ++ (int) noexcept
        { auto temp = *this; Base::operator++(); return temp; }

        const_reverse_iterator operator -- (int) noexcept
        { auto temp = *this; Base::operator--(); return temp; }

        const pair_t &operator * (void) const { return  cast(pointer(ptr)->data); }
        const pair_t *operator ->(void) const { return &cast(pointer(ptr)->data); }
    };

  private:

    implement impl;   /* Implement of compare and memory function. */
    node_base header; /* Parent as root node || son[0] as largest || son[1] as smallest. */

    /* Cast value_t to pair_t */
    static inline pair_t & cast(value_t &__v) 
    {  return reinterpret_cast <pair_t &> (__v) ;}

    /* Return the root node of the tree. */
    baseptr root() const noexcept { return header.parent; }

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

    /* Copy sub_tree information. Note that __p can't be null! */
    pointer copy(pointer __p) {
        pointer __c = impl.alloc(*__p); /* Current node. */
        if(__c->son[0]) {
            __c->son[0] = copy((pointer)__p->son[0]);
            __c->son[0]->parent = __c;
        }
        if(__c->son[1]) {
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
    template <class U>
    return_t insert_pair(U &&__v) {
        /* 
            In fact, this function was intended to support std::piecewise construct.
            However,it turned out that this is too much for me.
            I'm fed up . So you see such a function as below , like a piece of SHIT.
        */

        if(empty()) /* Just empty , so insert at root node. */
            return insert_root(impl.alloc(dark::tree::forward_tag(),
                                          std::forward <U> (__v)));

        baseptr __p = header.parent;
        bool dir;
        while(true) {
            if(impl (__v.first,pointer(__p)->data.first) ) {
                if(__p->son[0]) __p = __p->son[0];
                else { dir = 0; break; }
            }
            else if(impl (pointer(__p)->data.first,__v.first) )
                if(__p->son[1]) __p = __p->son[1];
                else { dir = 1 ;break; }
            else return {__p,false};
        }

        ++impl.count;
        __p->son[dir] = impl.alloc(dark::tree::forward_tag(),
                                   std::forward <U> (__v));
        __p->son[dir]->parent = __p;

        /* May update the largest / smallest. */
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
     * @return Pointer to the value. If not found return nullptr. 
     */
    T *access(const key_t & __k) const noexcept {
        baseptr iter = locate(__k);
        if(!iter) return nullptr;
        else return &pointer(iter)->data.second;
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
    return_t insert(const value_t &__v) { return insert_pair(__v); }
    /**
     * @brief Insert a key-value pair to the map.
     * If there exists indentical key, insertion will fail.
     *
     * @param __v Key-value pair to be inserted.
     * @return A pair of an iterator of the element and
     * a boolean of whether the insertion has been successful.
     */
    return_t insert(value_t &&__v) { return insert_pair(std::move(__v)); }

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
    void clear() noexcept {
        if(impl.count) {
            clean(root());
            initialize();
        }
    }

    T &operator [] (const key_t &__k) {
        /// TODO: Reduce the expansion of code as much as possible.
        throw ;
    }

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


/* Read function part. */

namespace dark {

/* Read a visible char. (Using standard ASCII.) */
char &read_char(char &ch) {
    do { ch = getchar(); } while(ch > 126 || ch < 33);
    return ch;
}

/* Read a signed integer. */
template <class integer>
integer &read_s(integer &num) {
    char ch;
    bool flag = false;
    num = 0;
    while(!isdigit(ch = getchar())) if(ch == '-') flag = true;
    while(isdigit(ch)) {
        num = num * 10 + (ch ^ '0');
        ch  = getchar();
    }
    if(flag) num = -num;
    return num;
}

/* Read an unsigned integer. */
template <class integer>
integer &read_u(integer &num) {
    char ch;
    num = 0;
    while(!isdigit(ch = getchar()));
    while(isdigit(ch)) {
        num = num * 10 + (ch ^ '0');
        ch  = getchar();
    }
    return num;
}

/* Special case : read a visible char. */
auto &read(char &ch) { return read_char(ch); }

auto &read(signed char  &num)  { return read_s(num); }
auto &read(signed short &num)  { return read_s(num); }
auto &read(signed int   &num)  { return read_s(num); }
auto &read(signed long  &num)  { return read_s(num); }

auto &read(unsigned char  &num) { return read_u(num); }
auto &read(unsigned short &num) { return read_u(num); }
auto &read(unsigned int   &num) { return read_u(num); }
auto &read(unsigned long  &num) { return read_u(num); }

auto &read(signed   long long &num) { return read_s(num); }
auto &read(unsigned long long &num) { return read_u(num); }

#ifdef __SIZEOF_INT128__ /* Special support for int128. */
auto &read(__int128_t &num)  { return read_s(num); }
auto &read(__uint128_t &num) { return read_u(num); }
#endif

auto &read(float &num)  { scanf("%f",&num) ; return num; }
auto &read(double &num) { scanf("%lf",&num); return num; }

#ifdef __SIZEOF_LONG_DOUBLE__
auto &read(long double &num) { scanf("%Lf",&num); return num; }
#endif

/* Read a visible string. (Using standard ASCII.) */
char *read(char *str) { 
    do { *str   = getchar(); } while(*str > 126 || *str < 33); 
    do { *++str = getchar(); } while(*str > 32 && *str < 127);
    *str = '\0';
    return str;
}


/* Read in a sequence of integers. */
template <class integer,class ...integers>
void read_s(integer &arg,integers &...args) { read_s(arg); read_s(args...); }
/* Read in a sequence of integers. */
template <class integer,class ...integers>
void read_u(integer &arg,integers &...args) { read_u(arg); read_u(args...); }
/* Read in a sequence of integers. */
template <class integer,class ...integers>
void read(integer &arg,integers &...args)   { read(arg);   read(args...); }



/* Paramless version. */


/* Read an integer any given type. */
template <class integer>
integer read() { integer tmp; return read(tmp); }
/* Read an unsigned integer of given type. */
template <class integer>
integer read_u() { integer tmp; return read_u(tmp); }
/* Read a signed integer of given type. */
template <class integer>
integer read_s() { integer tmp; return read_s(tmp); }
/* Read a visible char. */
char read_char() { char tmp; return read_char(tmp); }

/* Avoid misusage. */
template <class integer>
void read(integer &arg) = delete;

}

/* Write function part. */

namespace dark {

/* Write a integer. */
template <class integer>
void writeInt(integer num) {
    if(!num) return (void) putchar('0');
    if(num < 0) num = -num , putchar('-');
    static char ch[3 * sizeof(integer)];
    int top = 0;
    while(num) {
        ch[top++] = '0' ^ (num % 10);
        num /= 10;
    }
    while(top--) putchar(ch[top]);
}

/* Write a integer and start a new line.*/
template <class integer>
void writelineInt(integer num) {
    if(!num) return (void) puts("0");
    if(num < 0) num = -num,putchar('-');
    static char ch[3 * sizeof(integer) + 1] = {0};
    int top = 3 * sizeof(integer) - 1;
    while(num) {
        ch[--top] = '0' ^ (num % 10);
        num /= 10;
    }
    puts(ch + top);
}

/* Write an integer */

void write(signed char  num) { writeInt(num); } 
void write(signed short num) { writeInt(num); } 
void write(signed int   num) { writeInt(num); } 
void write(signed long  num) { writeInt(num); } 

void write(unsigned char  num) { writeInt(num); } 
void write(unsigned short num) { writeInt(num); } 
void write(unsigned int   num) { writeInt(num); } 
void write(unsigned long  num) { writeInt(num); } 

void write(signed long long   num) { writeInt(num); }
void write(unsigned long long num) { writeInt(num); }


void writeline(signed char  num) { writelineInt(num); } 
void writeline(signed short num) { writelineInt(num); } 
void writeline(signed int   num) { writelineInt(num); } 
void writeline(signed long  num) { writelineInt(num); } 

void writeline(unsigned char  num) { writelineInt(num); } 
void writeline(unsigned short num) { writelineInt(num); } 
void writeline(unsigned int   num) { writelineInt(num); } 
void writeline(unsigned long  num) { writelineInt(num); } 

void writeline(signed long long   num) { writelineInt(num); }
void writeline(unsigned long long num) { writelineInt(num); }



/* Write a char. */
void write (char _ch) { putchar(_ch); }
/* Write a char and start a new line. */
void writeline (char _ch) { putchar(_ch);putchar('\n'); }

/* Write a string. */
void write(char *__s) { while(*__s) { putchar(*(__s++)); } }
/* Write a string. */
void write(const char *__s) { while(*__s) { putchar(*(__s++)); } }

/* Write a string and start a new line. */
void writeline(char *__s) { puts(__s); }
/* Write a string. */
void writeline(const char *__s) { puts(__s); }


void write(float num)  { printf("%f" ,num); }
void writeline(float num)  { printf("%f\n" ,num); }

void write(double num) { printf("%lf",num); }
void writeline(double num) { printf("%lf\n",num); }

#ifdef __SIZEOF_LONG_DOUBLE__
void write(long double num) { printf("%Lf",num); }
void writeline(long double num) { printf("%Lf\n",num); }
#endif


/* Following is multiple-variable case. */

/* Special case. */

void write() {}
void writeline() { putchar('\n'); }


/* Write a sequence of integers , separated by ' '. */
template <class integer,class ...integers>
void write(const integer &arg,const integers &...args) {
    write(arg);
    putchar(' ');
    write(args...);
}
/* Write a line of integers , separated by ' '. */
template <class integer,class ...integers>
void writeline(const integer &arg,const integers &...args) {
    write(arg);
    putchar(' ');
    writeline(args...);
}

/* Print just one integer. */
template <class integer>
void print(const integer &arg) { write(arg); }

/* Print a sequence of integers without no separation. */
template <class integer,class ...integers>
void print(const integer &arg,const integers &...args) {
    write(arg);
    print(args...);
}

/* Print just one integer and start a new line. */
template <class integer>
void printline(const integer &arg) { writeline(arg); }

/* Print a line of integers without no separation. */
template <class integer,class ...integers>
void printline(const integer &arg,const integers &...args) {
    write(arg);
    printline(args...);
}

/* Avoid misusage. */
template <class integer>
void write(const integer &) = delete;
/* Avoid misusage. */
template <class integer>
void writeline(const integer &) = delete;



}

constexpr int M = 2.5e5 + 3;
constexpr int N = 5e4 + 9;
int s[N];
int cnt[N];
int ans[M];

struct node {
    int l,r,a,b,i;
} q[M];

inline int lowbit(int x) { return x & (-x); }
constexpr int sqr = 500;
inline int index(int x) { return (x - 1) / sqr; }

int n,m;
int pre[N];

inline void insert(int x) { while(x <= n) { ++pre[x]; x += lowbit(x); } }
inline void remove(int x) { while(x <= n) { --pre[x]; x += lowbit(x); } }
inline int query(int x) 
{ int sum = 0; while(x) { sum += pre[x]; x ^= lowbit(x); } return sum; }

inline void add(int x) { if(!cnt[x]++) insert(x); }
inline void del(int x) { if(!--cnt[x]) remove(x); }

struct cmp {
    bool operator() (const node &x,const node &y) const {
        int w = index(x.l) , z = index(y.l);
        if(w != z) return w < z;
        if(x.r != y.r) return w & 1 ? x.r > y.r : x.r < y.r; 
        return x.i < y.i;
    }
};


signed main() {
    dark::read(n,m);
    for(int i = 1 ; i <= n ; ++i) dark::read(s[i]);
    dark::map <node,cmp,cmp> t;
    node Q;
    for(int i = 0 ; i < m ; ++i) {
        dark::read(Q.l,Q.r,Q.a,Q.b) , Q.i = i;
        t.insert({Q,{}});
    }
    m = 0;
    for(auto &&i : t) q[m++] = i.first;
    int l = 1,r = 0; // range [l,r]
    for(int i = 0 ; i < m ; ++i) {
        while(r < q[i].r) add(s[++r]);
        while(l > q[i].l) add(s[--l]);
        while(r > q[i].r) del(s[r--]);
        while(l < q[i].l) del(s[l++]);
        ans[q[i].i] = query(q[i].b) - query(q[i].a - 1);
    }
    for(int i = 0 ; i < m ; ++i) dark::writeline(ans[i]);
    return 0;
}
