# 题面

在 C++ 中，我们通常用 `bool` 类型来存储一个要么是 $0$ 要么是 $1$ 的数。但是，`bool` 类型在内存中占用的空间是 $1$ 字节，即 $8$ bit，而我们实际只需要 $1$ bit 就可以存储一个 $0$ 或者 $1$。

因此，如果用一个 `bool` 数组来存储大量非 $0$ 即 $1$ 的数字，那么会造成空间的浪费。

这个时候，我们可以考虑用 **二进制压位** 的思想来存储这些数字。在 C++ 中，一个 `unsigned long long` 占 $8$ 个字节，有 $64$ 个 bit，我们可以用这 $64$ 个 bit 来存储 $64$ 个非 $0$ 即 $1$ 的数字。通过位运算，我们可以很方便地对其中的每一个 bit 进行操作。

二进制压位不仅能够节省空间，还能够极大地提高运算效率。例如，对于两个长度为 $n$ 的 $01$ 数组，我们想让他们进行与运算。如果用 `bool` 数组来存储，那么就需要进行 $n$ 次与运算。如果我们使用了二进制压位，那么我们只需要进行 $\lceil \frac{n}{64} \rceil$ 次与运算。

在 C++ 中，标准库提供了 `std::bitset` 类来实现二进制压位。具体可见 [cppreference](https://en.cppreference.com/w/cpp/utility/bitset) 。

但是，不幸的是，`std::bitset` 的长度是固定的，我们无法在运行时改变它的长度。因此，我们需要自己实现一个二进制压位的类，其长度可以在运行时动态改变，类似 `std::vector` 。

现给出接口如下:

```C++
#include <bitset> // 注意, C++11 标准以下没有这个头文件，用不到可以注释掉
#include <vector>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <algorithm>

struct dynamic_bitset {
    // 默认构造函数，默认长度为 0
    dynamic_bitset() noexcept = default;

    /**
     * @brief 拷贝构造函数
     * 如果你用 std::vector 来实现，那么这个函数可以直接 = default
     * 如果你手动管理内存，则你可能需要自己实现这个函数
     */
    dynamic_bitset(const dynamic_bitset &) = default;

    /**
     * @brief 拷贝赋值运算符
     * 如果你用 std::vector 来实现，那么这个函数可以直接 = default
     * 如果你手动管理内存，则你可能需要自己实现这个函数
     */
    dynamic_bitset &operator = (const dynamic_bitset &) = default;

    // 初始化 bitset 的大小为 n ，且全为 0.
    dynamic_bitset(std::size_t n);

    /**
     * @brief 从一个字符串初始化 bitset。
     * 保证字符串合法，且最低位在最前面。
     * 例如 a =  "0010"，则有:
     * a 的第 0 位是 0
     * a 的第 1 位是 0
     * a 的第 2 位是 1
     * a 的第 3 位是 0
     */
    dynamic_bitset(const std::string &str);

    // 如果不存在 1 ，则返回 true。否则返回 false
    bool none() const;
    // 如果不存在 0 ，则返回 true。否则返回 false
    bool all()  const;

    // 把第 n 位设置为指定值 val
    dynamic_bitset &set(std::size_t n, bool val = true);

    // 在尾部插入一个元素
    dynamic_bitset &push_back(bool val);

    // 返回自身的长度
    std::size_t size() const;

    /**
     * 所有位运算操作均按照以下规则进行:
     * 取两者中较短的长度那个作为操作长度。
     * 换句话说，我们仅操作两者中重叠的部分，其他部分不变。
     * 在操作前后，bitset 的长度不应该发生改变。
     * 
     * 比如 a = "10101", b = "1100"
     * a |= b 之后，a 应该变成 "11101"
     * b |= a 之后，b 应该变成 "1110"
     * a &= b 之后，a 应该变成 "10001"
     * b &= a 之后，b 应该变成 "1000"
     * a ^= b 之后，a 应该变成 "01101"
     * b ^= a 之后，b 应该变成 "0110"
     */

    // 或操作，返回自身的引用。     a |= b 即 a = a | b
    dynamic_bitset &operator |= (const dynamic_bitset &);
    // 与操作，返回自身的引用。     a &= b 即 a = a & b
    dynamic_bitset &operator &= (const dynamic_bitset &);
    // 异或操作，返回自身的引用。   a ^= b 即 a = a ^ b
    dynamic_bitset &operator ^= (const dynamic_bitset &);

    /**
     * @brief 左移 n 位 。类似无符号整数的左移，最低位会补 0.
     * 例如 a = "1110"
     * a <<= 3 之后，a 应该变成 "0001110"
     * @return 返回自身的引用
     */
    dynamic_bitset &operator <<= (std::size_t n);
    /**
     * @brief 右移 n 位 。类似无符号整数的右移，最低位丢弃。
     * 例如 a = "10100"
     * a >>= 2 之后，a 应该变成 "100"
     * a >>= 9 之后，a 应该变成 "" (即长度为 0)
     * @return 返回自身的引用
     */
    dynamic_bitset &operator >>= (std::size_t n);

    // 访问第 n 个位的值
    bool operator [] (std::size_t n) const;

    // 把所有位设置为 1
    dynamic_bitset &set     ();

    // 把所有位取反
    dynamic_bitset &flip    ();

    // 把所有位设置为 0
    dynamic_bitset &reset   ();
};



```

特别提醒: 请不要随意修改接口 (可能导致 CE) ! 但可以自行添加需要的成员函数和成员变量等等。

如果你不确定某个操作是否合法，请随时向助教提问。

# 数据范围

本题强制要求二进制压位，所有操作尽可能建立在压位的基础上实现。

| Subtask No. | Testcases No. | 前置Subtask | 额外考察的内容                                    | 分数   |
| ----------- | ------------- | ------------ | ---------------------------------------------------- | ------ |
| $1$       | $1$         | **无** | 考察压位、所有构造函数、下标运算符重载和 `size` 函数 | $10$ |
| $2$       | $2$         | $1$        | 考察 `push_back` 和 `set` 函数                   | $10$ |
| $3$       | $3$         | $1$        | 考察 `none` 和 `all` 函数                        | $10$ |
| $4$       | $4,5,6,7$   | $3$        | 考察 `set` ,`flip` 和 `reset` 函数             | $15$ |
| $5$       | $8,9,10,11$ | $2,4$      | 考察与、或、异或运算操作                             | $15$ |
| $6$       | $12,13,14$  | $2,4$      | 考察左移和右移运算操作                               | $15$ |
| $7$       | $15,16,17 $ | $5,6$      | 无 (全部考察，综合测试)                              | $15$ |
| $8$       | $18$        | $7$        | 内存泄露检查                                         | $8$ |
| $9$       | $19$     | **无** | (伪)随机~~卡常~~压力测试，可能涉及任何函数          | $1$  |
| $10$ | $20$ | **无** | (伪)随机~~卡常~~压力测试，可能涉及任何函数 | $1$ |
