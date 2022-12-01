#include <iostream>
#include <vector>
#include <functional>

class Defer {
  private:
    std::vector <std::function<void()>> stack;

  public:
    Defer() = default;
    Defer(std::function<void()> func) {
        stack.push_back(func);
    }
    void operator ()(std::function<void()> func) {
        stack.push_back(func);
    }
    ~Defer() {
        for(auto it = stack.rbegin() ; it != stack.rend() ; ++it)
            (*it)();
    }
};