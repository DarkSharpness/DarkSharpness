#ifndef _DARK_MAP_H_
#define _DARK_MAP_H_

#include <cstddef>
#include <memory>
#include <utility>

namespace dark {



/* BW_Tree */
enum class tree_color : bool { BLACK = 0 , WHITE = 1 };

using key_t   = int;
using value_t = long long;
using Compare = std::less <key_t>;


class map {
  public:

    struct iterator;
    struct const_iterator;
    struct node;
    struct allocator;

    using pair    = std::pair <key_t,value_t>;
    using pointer = node *;
    using Color   = tree_color;

  protected:

    /* Right rotate. */
    void zig(pointer &cur) {
        pointer tmp = cur->ls;
        cur->ls = tmp->rs;
        tmp->rs = cur;
        cur = tmp;
    }

    /* Left rotate */
    void zag(pointer &cur) {
        pointer tmp = cur->rs;
        cur->rs = tmp->ls;
        tmp->ls = cur;
        cur = tmp;
    }

    /* Find the first node no less than. */
    std::pair <pointer,int> lower_bound(const pair &obj) {
        pointer last = nullptr;
        pointer temp = root;
        while(true) {
            if(Compare()(obj.first,temp->data.first)) {
                last = temp;
                temp = temp->ls;
                if(!temp) return std::make_pair(last,-1);
            } else if(Compare()(temp->data.first,obj.first)) {
                last = temp;
                temp = temp->rs;
                if(!temp) return std::make_pair(last,1);
            } else { return std::make_pair(temp,0); }
        }
    }


  public:



    std::pair <iterator,bool> insert(const pair &obj) {
        if(!root) {
            root = A.alloc(nullptr,nullptr,nullptr,obj);
            root->color = Color::BLACK;
            return std::make_pair(root,true);
        }

        auto result = lower_bound(obj);
        if(!result.second) return std::make_pair(result.first,false);

        pointer temp = A.alloc(nullptr,nullptr,result.first,obj);
        if(result.second > 0) temp->fa->rs = temp;
        else/* .second < 0 */ temp->fa->ls = temp;
        
        while(temp->fa && temp->fa->color == Color::WHITE) {
            // if()
        }

        root->color = Color::WHITE;
    }

    void erase(iterator pos) {
        
    }



  public:

    






  protected:

    struct node {
        using Color = tree_color;

        pointer ls; // Left  son
        pointer rs; // Right son
        pointer fa; // Father
        Color color; // Color information
        std::pair <key_t,value_t> data; // Inner data holder.

        /* Initialize from Args. */
        template <class ...Args>
        void init(pointer _l,pointer _r,pointer _f,Args &&...objs) {
            ls = _l;
            rs = _r;
            fa = _f;
            color = Color::WHITE;
            data  = pair(std::forward <Args> (objs)...);
        }

        node(pointer _l,pointer _r,pointer _f,std::pair <key_t,value_t> &&temp) 
            noexcept : 
            ls(_l),rs(_r),fa(_f),color(Color::WHITE),data(std::move(temp)) {}
        node(pointer _l,pointer _r,pointer _f,const std::pair <key_t,value_t> &temp) 
            : ls(_l),rs(_r),fa(_f),color(Color::WHITE),data(temp) {}
    };

    class allocator : private std::allocator <node> {
        pointer head; /* Buffer list head. */
        pointer tail; /* Buffer list tail. */
      public:
        /* Empty allocator. */
        allocator() noexcept : head(nullptr),tail(nullptr) {}
        /* Empty allocator. */
        allocator(const allocator &rhs) noexcept : allocator() {}
        /* Just take all the buffer. */
        allocator(allocator &&rhs) noexcept : head(rhs.head),tail(rhs.tail) 
        {   rhs.head = rhs.tail = nullptr;    }
        ~allocator() noexcept { remove_buffer(); }

        /* Doing nothing to the allocator. */
        allocator &operator = (const allocator &rhs) noexcept {};
        /* Merge 2 buffer list. */        
        allocator &operator = (allocator &&rhs) noexcept {
            if(!tail) {
                std::swap(head,rhs.head);
                std::swap(tail,rhs.tail);
            } else if(rhs.head) { /* Link 2 lists. */
                tail->rs = rhs.head;
                rhs.head->ls = tail;
                tail = rhs.tail;
                rhs.head = rhs.tail = nullptr;
            } else ; /* Nothing is done in this case.  */
        }

        /* Allocate one node and initialize it. */
        template <class ...Args>
        pointer alloc(pointer _l,pointer _r,pointer _f,Args &&...objs) { 
            if(!head) {
                pointer temp = this->allocate(1);
                this->construct(temp,_l,_r,_f,std::forward <Args> (objs)...);
                return temp;
            } else {
                pointer temp = head;
                if(head == tail) head = tail = nullptr;
                else head = head->rs;
                temp->init(_l,_r,_f,std::forward <Args> (objs)...);
            }
        }

        /* Return the node back to buffer area. */
        void dealloc(pointer temp) {
            temp->rs = head;
            temp->ls = nullptr;
            if(head) head->ls = temp;
            else         tail = temp;
            head = temp;
        }

        /* Clean buffer list. */
        void remove_buffer() noexcept {
            while(head) {
                tail = head->rs;
                this->destroy(head);
                this->deallocate(head,1);
                head = tail;
            }
            /* Now head = tail = nullptr. */
        }
    };

    pointer root; /* Pointer of root node. */
    allocator A;  /* Allocator of memory. */
    size_t count; /* Count of all nodes. */

    class iterator { 
      public: 
        pointer ptr;
        iterator(pointer __p = nullptr) noexcept : ptr(__p) {}

    };
    class const_iterator { public: pointer ptr; };


};





}


#endif
