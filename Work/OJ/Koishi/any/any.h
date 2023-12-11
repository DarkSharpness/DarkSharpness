#pragma once
#include <new>
#include <utility>
#include <stdexcept>
// 你不可以使用任何其他的头文件

namespace koishi {

/**
 * @brief 一个可以存储任意类型的类 (确信)。
 * 其要么存储了某个类型的值，要么为空(不存储任何值)。
 */
class any {
  private:
    // 你不可以额外添加任何成员变量。
    // base 类的实现在 any 类的尾部。
    // 你需要通过观察 base 和 storage 类的实现来完成 any 类的实现。

    struct base;
    base *ptr = nullptr; // 指向基类的指针

  public:
    // 默认构造函数，创建一个空的 any 对象。
    any();

    // 你同样可以使用 nullptr 来创建一个空的 any 对象。
    any(std::nullptr_t) : any() {}

    // 销毁当前对象。
    // 重申: delete nullptr 是安全的。
    ~any();

    // 拷贝构造函数，创建一个和 other 一样的 any 对象。
    // 可能要用到 clone() 函数
    any(const any &other);

    // 移动构造函数，创建一个和 other 一样的 any 对象。
    // 你只需要移走 other 的数据，使得 other 为空即可。
    // 你不应该用到 clone() 函数
    any(any &&other);

    // 创建一个存储了某个类型的值的 any 对象。
    // 你不用管模板的第二个参数。那是用来约束 T ，保证 T 不是 any 类型的。
    template <typename T, typename = std::enable_if_t<!std::is_same_v<std::decay_t<T>, any>>>
    any(const T &);

    // 拷贝赋值运算符，要求类似拷贝构造函数。
    any &operator = (const any &other);

    // 移动赋值运算符，要求类似移动构造函数。
    any &operator = (any &&other);

    // 强行把当前对象转换成 T 类型。
    // 如果当前存储的不是 T 类型的值，那么抛出异常 std::bad_cast
    template <typename T>
    T &cast();

    // 差不多，但是是 const 版本的。
    template <typename T>
    const T &cast() const;

    // 尝试把当前对象转换成 T 类型。
    // 如果当前存储的不是 T 类型的值，那么返回 nullptr
    template <typename T>
    T *try_cast();

    // 差不多，但是是 const 版本的。
    template <typename T>
    const T *try_cast() const;

    // 判断当前对象是否为空。
    bool is_empty() const;

  private:

    // 以下是 base 类和 storage 类的实现。
    // 你可以思考一下为什么要这么设计。
    // 事实上 any 类的设计并不唯一，标准库也并不是这么写的
    // 标准库使用函数指针那种写法，我觉得还是这种写法比较好理解些。

    struct base {
        virtual ~base() = default;
        virtual base *clone() const = 0;
    };

    template <typename T>
    struct storage : base {
        T value; // 真实的数据存储在这里哦

        // 完美转发，接受任意类型的参数
        // 现在 storage  T 所有的构造函数了
        template <typename Args>
        storage(Args &&args) : value(std::forward <Args>(args)) {}

        // 拷贝一份自己，返回基类的指针。
        base *clone() const override { return new storage(value); }
    };
};


} /* namespace koishi */

