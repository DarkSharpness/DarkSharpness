### Dark 教授的挑战 9.0

#### 题目描述

Dark 教授有一串数字 x1,x2...,xn ，他希望你求出第 l 个 到 第 r 个数字的和 xl + ... + xr

特别地，Dark 教授提醒您，可以通过记录前缀数组 st = x1+...+xt 来快速求出答案，这种思想叫做前缀和，在信息竞赛中经常用到。

#### 输入描述

第一行两个正整数 n 和 q，表示数组的长度和询问的个数。

后面一行 n 个整数，表示数组的 n 个数。

后面 q 行，每行两个正整数 l 和 r ，表示一组询问。

保证输入合法，且输入整数绝对值不超过 100。

#### 输出描述

q 行，每行一个整数，表示对应询问的答案。

#### 输入样例
```
5 3
1 4 1 3 2
1 3
2 5
4 4
```
#### 输出样例
```
6
10
3
```