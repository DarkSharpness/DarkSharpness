#include <iostream>

// no inline, required by [replacement.functions]/3
void* operator new(std::size_t sz) {
    std::printf("new(), size = %zu\n", sz);
    if (sz == 0)
        ++sz; // avoid std::malloc(0) which may return nullptr on success
 
    if (void *ptr = std::malloc(sz))
        return ptr;

    throw std::bad_alloc{}; // required by [new.delete.single]/3
}
 
void operator delete(void* ptr) noexcept {
    std::puts("delete()");
    std::free(ptr);
}
 
void operator delete(void* ptr, std::size_t size) noexcept {
    std::printf("delete(), size = %zu\n", size);
    std::free(ptr);
}

#include "src.hpp"

namespace dark {
struct base {
    virtual ~base() = default;
    virtual base *clone() const = 0;
};

template <typename T>
struct storage : base {
    T value; // 真实的数据存储在这里哦

    // 完美转发，接受任意类型的参数
    // 现在 storage 有 T 所有的构造函数了
    template <typename Args>
    storage(Args &&args) : value(std::forward <Args>(args)) {}

    // 拷贝一份自己，返回基类的指针。
    base *clone() const override { return new storage(value); }
};

} /* namespace dark */

signed main() {
    using koishi::any;
    any x;
    x = nullptr;
    static_assert (sizeof(dark::storage <std::string>) == 40);
    x = std::string();
    x = nullptr;
    if (x.try_cast <std::string> ()) std::exit(1);
    return 0;
}
