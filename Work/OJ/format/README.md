# 题面

现在，你需要实现一个模板函数 `format` ，其可以动态地解析字符串并且格式化输出字符串，行为和 `C++20` 中的 `std::format` 类似。声明如下:

```C++
namespace sjtu {
template <typename ...Args>
std::string format(std::string_view fmt, Args &&...args);
} // namespace sjtu
```

传入的第一个参数 `fmt` 为格式串，格式串中的 `{}` 会被按顺序替换为对应的参数，例如:

```C++
// 应该得到字符串 "Hello, world 2024!"
std::string str = sjtu::format("Hello, {} {}!", "world", 2024);
```

特别地，我们可以使用 `{{` 和 `}}` 来转义表示 `{` 和 `}` ，即 `{{` 会被替换为 `{` ，`}}` 会被替换为 `}` ，例如:

```C++
// 应该得到字符串 "Hello, {world}!"
std::string str = sjtu::format("Hello, {{{}}}!", "world");
```

除了 `{}` 之外，我们还可以使用 `{n}` 来表示第 `n` 个参数。

```C++
// 应该得到字符串 "Hello, world!"
std::string tmp = "Hello";
std::string str = sjtu::format("{1} {0}!", "world", tmp);
```

特别地，以下是一些非法行为，需要抛出异常 `std::runtime_error` :

- 将 `{n}` 和 `{}` 混用。

- 使用 `{}` 替换参数，且传入参数数量少于 `{}` 的数量。

- 使用 `{n}` 替换参数，且 `n` 超过了传入参数的数量，或者 `n` 不是一个合法的非负整数。

- 存在未配对的 `{` 和 `}` 。

## 前置芝士

- `std::string_view` (C++17)
- 左值和右值 (C++11)
- 可变长参数模板 (C++11)

## 可选芝士

- 引用折叠 (C++11)
- 完美转发 (C++11)
