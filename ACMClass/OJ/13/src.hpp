// "Wrapper": src.hpp
#ifndef Wrapper_CPP_Wrapper_HPP
#define Wrapper_CPP_Wrapper_HPP
#include <string>

struct Wrapper;

using wptr = Wrapper *;

struct Wrapper {
    // todo: add definitions here
    wptr next,prev;
    void (*func)(std::string id);
    void (*before)();
    void (*after)();
    void work(const std::string &str) {
        before();
        func(str);
        after();
    }
    Wrapper() {
        prev = next = this;
    }
};
// todo: add definition for link list
Wrapper empty_node;
wptr node = &empty_node;
// todo: create()
template <class T,class V>
wptr create(V func,T begin,T end) {
    wptr temp = new Wrapper;
    node->next->prev = temp;
    temp->next = node->next;
    temp->prev = node;
    node->next = temp;
    temp->func   = func;
    temp->before = begin;
    temp->after  = end;
    return temp;
}
// todo: remove()

void remove(wptr ptr) {
    ptr->prev->next = ptr->next;
    ptr->next->prev = ptr->prev;
    delete ptr;
    ptr = nullptr;
}


// todo: run()
void run(wptr ptr,const std::string &str) {
    ptr->work(str);
}


// todo: destroy()
void destroy() {
    wptr temp = node->next;
    while(temp != node) {
        temp = temp->next;
        delete temp->prev;
    }
    node->next = node->prev = node;
}
#endif //Wrapper_CPP_Wrapper_HPP