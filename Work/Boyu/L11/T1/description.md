### Dark 教授的挑战 8.0

#### 题目描述

Dark 教授有一些点，它们之间有一些边。现在，Dark 教授告诉了你所有边的情况。她希望你能回答出某两个点之间是否有边直接相连，你能完成她的挑战吗?

#### 输入描述

第一行两个整数m，q 分别表示边数和询问个数。

后面 m 行，每行两个正整数x，y，表示点 x 和点 y 之间由一条边。

最后 q 行，每行两个正整数x，y，表示一组询问，询问 x 和 y 之间有没有一条边。

保证所有输入整数不超过 500。

#### 输出描述

q 行，每行对应一组询问。

如果询问的两个点之间没有边直接相连，则输出 No

否则，输出 Yes

#### 输入样例
```
2 3
1 2
1 3
2 1
1 3
2 3
```
#### 输出样例
```
Yes
Yes
No
```