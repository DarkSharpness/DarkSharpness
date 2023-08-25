# 生存战争 规则与说明:

目前 mc 版本 : 1.20（23w18a）- 1.20.1

**游戏难度为：简单**（就这还有人PvL/PvZ/PvB失败怎么敢改普通的）

## 1.坤本规则

注意: 文章中可能会出现某些大写字母，作为游戏参数。问就是没填

生存战争 (Survival War)，类似原版 UHC，属于原版生存类 pvp ，但是难度有十分甚至九分的下调。玩家一开始被限制边长为880左右的正方形区域内 (包括主世界和下界) ，2支队伍初始被分配到不同的角落。所有玩家初始一无所有（有个指南针……算了），从 0 开始生存，玩家需要在存活下来的同时发育，并且消灭敌队，死亡后可以复活 ~~（但是你都爆金币了难道空手平A吗）~~ 。 当场上只有一只队伍的时候，该队伍获胜。

比赛开始前，玩家可以选技能：

主动技能默认手持指南针按F，没反应要么CD要么没有技能

```
"职业：",{"text": "§a§n传送",                                                                                 "手持指南针按[",{"keybind": "key.swapOffhand"},"]释放\n[传送]冷却:4min，立即传送至一名队友身边，为其提供4护盾持续3s"]},                                                                                                         0", "  ",

{"text": "§a§n狩猎",                                                                                                            "指南针附魔§d抢夺§r，对大多数怪物有伤害加成，手持按[",{"keybind": "key.swapOffhand"},"]释放[火风]\n[火风]冷却:10s，烧死5格内的狩猎目标生物，包含绝大多数怪物和资源生物，并吸收6格内资源。\n"]}

{"text": "§a§n深潜",                                                                                                         "移速×1.05，获得潮涌能量与海豚的恩惠\n开局获得15饱和度

{"text": "§a§n防御",                                                                                                            "获得20韧性与100%击退抗性

{"text": "§a§n隐行",                                                                                                            "在敌方玩家6格外隐身，此时不会发光

{"text": "§a§n切裂",                                                                                                            "（未完成）[切裂]冷却:90s，将6格内所有或15格内1名敌方玩家降低<⅙已损生命>点生命值，若击杀则冷却降至6s。无效果时不会释放。"

{"text": "§a§n御守",                                                                                                            "（未完成）[御守]冷却:90s，获得80%免伤，攻速×1.5，近战伤害×0.1，持续10s"

终结
（未完成）被玩家击杀后3s释放炸弹，期间持续吸引实体

{"text": "§a§n闪现
未完成）[闪现]：冷却:180s，如果视线前方5格附近为可落脚点，闪现至此处，无效果时不会释放。
```

我焯，原（代码）！

在比赛开始前，有 **5s** 观察时间（一眼丁真）。在观察阶段，你不能动。然后就开始罢！

在比赛开始后，玩家将会获得永久夜视（姑且让我这么说罢，但是真正的强者，其实没有给你们夜视！玩家还是能看出光照的变化的，只不过洞里没那么黑了） 和 **12min** (相当于第一个白天) 隐身和锋利I，以及（逐渐衰减的）急迫（不加攻速别想了，不过挖掘速度真的很快）、速度、跳跃提升（4min就没了，能跳2格，珍惜吧）。

12分钟过了还是有一定急迫，这是为了平衡挖/放

隐身保护的时候……6格内有敌方玩家，只能再隐身5秒，3格内立即暴露。



## 2.其他规则以及要求

以下是一些 **能** 做的事情:

* [X] 观察者在6格内汇报信息（只要自己在活队友6格内，透视也是允许的）
* [X] 使用材质包，若其不违反规则（如红石显示）
* [X] 在你所热爱的，就是你的生活的网站直播
* [X] 利用原版 bug (如卡出透视)， 以及原版信息 (如 F3)
* [X] 协商后，补偿由于服务器卡顿、玩家视力不均衡带来的损失
* [X] 在alpha2.0.0版本，使用 /kill 指令自杀，这意味着之后的版本可能取消这一选项

以下是一些 **不能** 做的事情:

* [ ] 卡服/崩服
* [ ] 使用超过原版信息的 mod ，或 资源包 (如小地图/xray矿透)
* [ ] 观察者汇报队友视野外信息(报点)（设计上他们不能离开活队友6格内）
* [ ] 未经允许使用违规指令
* [ ] 赛前研究比赛场地
* [ ] 赛前在比赛场地进行交互

**此外，您还需要遵守VMcP协议！在询问时需公开你所使用的客户端，所有使用的MOD，以及资源包，并且不建议使用原版或Fabric以外的客户端。**

## 3.一些细节

### 修改：

镐子可以快速破盾（2下盾就残了）

锄头可以让使用盾的玩家转向约180（随机偏移），并对周围3格内的敌方玩家造成伤害(0.5)，将4格内敌方玩家并向自己吸引。

锹可以让击中玩家（有伤害才行）附近的敌方转向3~12度

**喜欢盾斧吗**

x:皮革/铜块,o:兔子皮/铜锭（可混合）

皮革帽子：

xox<br>
o_o

皮革胸甲：

o_o<br>
xxx<br>
x_x

皮革裤子：

xox<br>
x_x<br>
o_o

皮革鞋子：

o_o<br>
x_x

铁、钻石装备合成额外需要一个低等级装备。


铁斧：X铁块，O铜块

XOX<br>
XO<br>
_O

铁剑：M铁锭，O铜块，W铜锭<br>
MO<br>
MO<br>
_W

钻石斧：X钻石，W铜锭，P铁斧

XPX<br>
XW<br>
_W

铁剑：X钻石，P铁剑，W铜锭<br>
_X<br>
XP<br>
_W


**熔炉烧矿物速度增加100%**

### 增加

皮革：可以拆成9个兔子皮

矿块指铜铁金块，粗同理

书x1：<br>
铜块 纸<br>
铜块 纸<br>
铜块 纸<br>

快速熔炼：<br>
粗矿 碳（任意） 粗矿<br>
粗矿 熔炉/高炉  粗矿<br>

锻造：
铁/钻石 装备/武器工具 +模板+ 原石/深板岩原石 = 升级装备 （钻石/合金）

花费2倍时间（20s），熔炼粗矿块为矿块

**看着很多，实际上游戏里都有配方书**

## 4.游戏行进

记游戏正式开始的相对时间为 0 :

### 游戏模式：随机出生点

| 距开始时间       | 大致事件                                         |
| ------------------- | ------------------------------------------------ |
| -15s                 | 游戏准备，玩家可以最后调整队伍                   |
| -5s                 | 两队玩家进入随机出生点（0,0周围80格范围，距离最小80） |
| 0                   | 游戏正式开始，玩家12分钟逐渐衰减的信标增益       |
| 12min                | 夜幕降临，信标增益、隐身保护消失，准备战斗！     |
| 12min                | 开始缩圈（速度逐渐减小）                     |
| 28min               | 底部缩圈，至y=12为止                           |
| 39min               | 缩至2×2                                   |
| 40min               | 玩家持续收到近战伤害（盾牌可挡20%）            |


### 游戏模式：飞行 *（正在调试）*

| 距开始时间       | 大致事件                                         |
| ------------------- | ------------------------------------------------ |
| -15s                 | 游戏准备，玩家可以最后调整队伍                   |
| -10s                 | 玩家上飞机 |
| 0                   | 游戏正式开始，玩家12分钟逐渐衰减的信标增益，可以下飞机|
| 12min                | 夜幕降临，信标增益、隐身保护消失，准备战斗！     |
| 12min                | 开始缩圈（速度逐渐减小）                     |
| 28min               | 底部缩圈，至y=12为止                           |
| 39min               | 缩至2×2                                   |
| 40min               | 玩家持续收到近战伤害（盾牌可挡20%）            |

> $\copyright$ 2023 lytDARK - Survival War 保留所有权利