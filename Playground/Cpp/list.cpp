#include <iostream>
#include <memory>
#include <list>
#include "memory.h"


struct node {
    node *prev;
    std::unique_ptr <node> next;
    size_t data;
};


signed main() {
    return 0;
}