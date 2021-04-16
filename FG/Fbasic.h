#ifndef __FG_BASIC_
#define __FG_BASIC_
#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ul;
typedef double lf;
typedef unsigned int ui;
typedef char ch;
using namespace std;

/**
 * @brief FingerGlory 命名空间
 * 防止误操
 */
namespace FG{


//这些参数以后是输入的
const ll T=5   ;//武器属性总量
const ll A=101 ;//武器总数

/**
 * @brief 武器结构体
 * @param name 名字
 * @param FGid FG的序号ID
 * @param type 操作类型
 * @param dam 伤害计数器
 * @param spd 速度因子
 */
struct weapon{
    string name;    //名字
    ui FGid;        //FingerGlory ID
    
   
    /*
      --type 类型参数--
      在标准FG中 
      1,是攻击类
      2,是防御类
      3,是弹类
      4,是技能类
     */
    ch type;
    /*
        --伤害计数器--
        在标准FG中
        下标0的是记录数据用:
            如果是攻击类,记录攻击目标数量,如果=0则是群伤
            如果是防御类,则具体记录攻击目标
    */
    vector <lf> dam;    
    vector <lf> spd;    //速率因数
    bool operator <(const weapon &b)const{
        return FGid<b.FGid;
    }
    weapon()
    {
        dam.clear();
        spd.clear();
        dam.resize(T+1);
        spd.resize(T+1);
        name="";
        type=FGid=0;

    }

}w[A];

}


#endif