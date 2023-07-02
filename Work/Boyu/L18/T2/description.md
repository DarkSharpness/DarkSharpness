### 高精度排序

#### 出题人 : DarkSharpness

#### 题目描述

现在你有若干个高精度正整数，你要对其排序。

为了降低难度，保证待排序的正整数的数量不超过 100 ，且每个正整数在十进制下不超过 100 位。因此，你可以直接用最简单的冒泡排序完成排序，可以不用 std::sort 解决这道题。

#### 输入描述

第一行一个正整数 n ，表示正整数的总数。

后面 n 行，每行一个正整数。

#### 输出描述

从小到大，每行一个排序好的正整数。

#### 输入样例

```
3
114514114514114514114514114514
191981019198101919810
191981019198101919810114514114514
```

#### 输出样例

```
191981019198101919810
114514114514114514114514114514
191981019198101919810114514114514
```