### Dark 教授的挑战 20.0 —— 快速排序

#### 题目描述

Dark 教授听说你学过了快速排序，于是决定考查你快速排序。当然，简单的快速排序模板没有什么好考察的，她知道你们会用 std::sort 轻松的通过题目，于是她决定考察你如何将其用于实际。

现在 Dark教授给了你若干个有序 (从小到大) 的数组。现在，她有如下两个指令:

- add x y 把数组 y 的全部元素加入数组 x ，依然保持数组 x 有序
- print x 按照顺序输出数组 x 的所有元素

她要求你能按照要求输出即可。当然，这道题是允许用 std::sort 的啦 !

特别地，为了避免超时，Dark 教授提供了快速读写的模板。

附: Dark 教授的快速读写模板

```C++
#include <iostream>

/* 读入一个正整数. */
template <class integer>
integer read() {
    char ch;
    bool flag = false;
    integer num = 0;
    while(!isdigit(ch = getchar()));
    while(isdigit(ch)) {
        num = num * 10 + (ch ^ '0');
        ch  = getchar();
    }
    if(flag) num = -num;
    return num;
}

/* 写一个正整数(无空格/换行) */
template <class integer>
void write(integer num) {
    if(!num) return (void) putchar('0');
    static char ch[24];
    int top = 0;
    while(num) {
        ch[top++] = '0' ^ (num % 10);
        num /= 10;
    }
    while(top--) putchar(ch[top]);
}


/* 使用样例 */ 
void test() {
    int x,y;

    // 读入正整数 x 和 y
    x = read <int> ();
    y = read <int> ();

    // 输出一个正整数 x + y
    write(x + y);

    // 输出空格
    putchar(' ');
    // 输出换行
    putchar('\n');
}


```


#### 输入描述

一行两个正整数 $n$ 和 $m$ ，分别是数组的总数和指令的总数。

后面 $n$ 行每行先是一个正整数 $s_x$ ，表示数组的长度，然后是 $s_x$ 个正整数，表示数组中的每个数字。

后面 $m$ 行，每行一条指令。

保证 $n$ 不超过 $32$ ，$m$ 不超过 $1 \times 10 ^ 4$ ，且中间过程任一数组长度不超过 $1 \times 10 ^ 5$ 。保证所有输入正整数在 int 范围内，且输入的每个正整数数组有序。

#### 输出描述

每个 print 指令对应一行输出，表示该数组中的全部元素。一行输出内，正整数之间用一个空格隔开。

保证输出的正整数的数量不会超过 $1 \times 10 ^ 6$ 

#### 输入样例

```
3 5
3 1 3 5
3 2 4 6
1 7
add 1 2
print 1
print 2
add 3 1
print 3
```

#### 输出样例

```
1 2 3 4 5 6
2 4 6
1 2 3 4 5 6 7
```

#### 样例解释

第一条 add 指令后，数组 $1$ 变为 [1,2,3,4,5,6] ，数组 $2$ 不变

第二条 add 指令后，数组 $3$ 变为 [1,2,3,4,5,6,7]
