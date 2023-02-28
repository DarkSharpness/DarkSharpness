#ifndef _DARK_MAP_H_
#define _DARK_MAP_H_

#include <cstddef>
#include <cstdlib>
#include <functional>

namespace dark {



/* BW_Tree */
enum class tree_color : bool { BLACK = 0 , WHITE = 1 };

using key_t   = int;
using T = long long;
using Compare = std::less <key_t>;

class map {
  public:

    struct node;
    struct allocator;
    struct iterator;
    struct const_iterator;

    using value_t = std::pair <key_t,T>;
    using Color   = tree_color;
    using pointer = node *;

  private:


    struct node {
        pointer son[2];
        pointer fa;
        Color color;
        value_t data;
        node()  {}

        node(value_t &&__data) noexcept
            : son({nullptr,nullptr}) , fa(nullptr) , color(Color::WHITE), 
              data(std::move(__data)) {}

        node(const value_t &__data)
            : son({nullptr,nullptr}) , fa(nullptr) , color(Color::WHITE), 
              data(__data) {}

        ~node() = default;

        bool direction() const noexcept { return ; }
    };

    struct allocator {
        size_t count;
        allocator() = default;
        allocator(const allocator &) noexcept = default;
        allocator & operator = (const allocator &) =  default;


        pointer alloc() {
            ++count;
            return (pointer) std::malloc(sizeof(node));
        }

        template <class ...Args>
        void construct(pointer __p,Args &&...objs) {
            ::new ((void *)__p) node(std::forward <Args> (objs)...);
        }

        void dealloc(pointer __p) {
            --count;
            __p->~node();
            std::free(__p);
        }

    };


    allocator A;
    pointer root;

    void rotate(pointer cur) {
        booo dir = 

    }

  public:



};





}


#endif
