### 数组压缩

#### 题目描述

现在，你有一个长度为 $n$ 的正整数数组，你需要对其进行压缩。具体来说，你需要从小到大输出出现了某一次数的正整数有哪些。格式如下:

例如，对于数组 [1,2,1,1,2,4,5,2,3] ，出现了一次的正整数有 3 和 4 和 5 ，出现三次的正整数为 1 和 2 。

因此，你需要先输出一行 1 : 3 4 5 表示出现一次的正整数从小到大为 3 4 5。然后，你要输出一行 3 : 1 2 表示出现三次的正整数从小到大为 1 2 。

特别地，若出现特定次数的正整数不存在，则不用输出。

附: 快读模板(防止超时)

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

第一行一个正整数 $n$ 表示正整数数组的长度。

第二行 $n$ 个正整数，表示这个数组。

保证 $n$ 不超过 $10 ^ 6$ 并且所有输入正整数在 int 范围内。

#### 输出描述

若干行，每行开头输出一个正整数，表示出现次数，然后输出一个冒号，然后从小到大输出出现该次数的所有正整数。正整数之间、正整数和冒号之间两两用空格隔开。

#### 输入样例

```
9
1 2 3 1 2 3 4 1 1
```

#### 输出样例

```
1 : 4
2 : 2 3
4 : 1
```
