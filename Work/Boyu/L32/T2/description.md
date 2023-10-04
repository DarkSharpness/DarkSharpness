### Minecraft 无限水

#### 题目描述

在知名游戏 Minecraft 中，存在一种有趣的机制，叫做无限水。其简化版本大致如下:

对于一个空气方块，如果其相邻的东南西北四个方向存在不少于两个水源方块，那么其在下一时刻会变为水源方块，

现在，给定初始的水源分布，求出足够长时间之后的水源分布情况 (不考虑真实 mc 中的水的流动) 。

#### 输入描述

第一行两个正整数 $n$ 和 $m$ 表示地图的长度与宽度。

后面 $n$ 行，每行 $m$ 个字符，表示初始水源分布情况。

其中，字符 - 表示 水源方块。字符 * 表示 空气方块。字符 # 表示实体方块(不可转化为水源方块)。

保证 $n$ 和 $m$ 不超过 $100$

#### 输出描述

足够长时间之后的水源分布情况。(可以证明，该情况唯一)。

#### 输入样例


```
5 5
**#--
***-*
#*-**
*-*#*
-***-
```



#### 输出样例

```
**#--
*----
#----
---#-
-----
```