# OJ Hacker

Prof. Dark 今天非常不开心，他打算让所有人今天都拿不到分。于是，他搬运了过去出的几道模板类的题目，使用 special judge 测评。

因此，你需要提交一份头文件，使得他的代码能够编译通过，且输出 "Accepted" 以及其他的校验信息 (防止你的模板类直接 terminate 手动输出 AC，只要正常运行一定会输出)。但是，他没有告诉你具体要实现什么。这可如何是好！

提示：你可以试着交一下以下这份代码。

```C++
#pragma once
#ifndef FUCK_DARKSHARPNESS
#define FUCK_DARKSHARPNESS
#endif
```