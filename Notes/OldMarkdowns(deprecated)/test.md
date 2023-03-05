Recently, when I am testing the implement of std::vector, I found that when the capacity of an vector grows, it uses copy construction to initialize the objects in the newly-allocated memory, rather than move construction.
In my point of view, when the capacity of an vector grows, the old objects become useless. Therefore, I think they should be moved, but not copied. If the objects are costly to copy but easy to move (e.g. std::string) , then the current implement of std::vector is rather slow!


Can somebody explain the reason for me? Thanks so much!

Here's my code for test.(Windows,-std=c++14)

```C++
// Testing the implement of standard C++ library.
#include <iostream>
#include <vector>

struct object {
    void * ptr;
    size_t val;
    object() {std::cout << "Construction.\n";}
    object(object &&) {std::cout << "Move Construction.\n";}
    object(const object &) {std::cout << "Copy Construction.\n";}
    object &operator = (object &&) {
        std::cout << "Move Assignment.\n";
        return *this;
    }
    object &operator = (const object &) {
        std::cout << "Copy Assignment.\n";
        return *this;
    }
};

inline void printline() {std::cout << "----------------------\n";}

signed main() {
    std::vector <object> test(2);
    printline();
    test.resize(3);
    printline();
    return 0;
}

```

Output:

```
Construction.
Construction.
----------------------
Construction.
Copy Construction.
Copy Construction.
----------------------
```
