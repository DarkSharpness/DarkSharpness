#ifndef __FG_BASIC_
#define __FG_BASIC_
#include <DarkSharpness/FG/Fmath.h>
#include <DarkSharpness/C++_Templates/statue.h>

/**
 * @brief FingerGlory 命名空间
 * 防止误操
 */
namespace FG{


//这些参数以后是输入的
const ll T=5   ;//武器属性总量
const ll A=101 ;//武器总数


//状态记录




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
    //记录对应的是哪几位
    statue <96> st;
    /*
        --伤害计数器--
        下标0的是记录数据用:
            如果是攻击类,记录攻击目标数量,如果=0则是群伤 =-1是判定群伤
            如果是防御类,则具体记录属于什么类
                2^1 普防类(有防御能力)
                2^2 积点类(可主动积点)
                2^3 不出类(FG特性)
            如果是弹类,记录弹力上限.如果<0,则是自爆弹.
        下标i(i>0) 
            type=1,2才记
            记录什么类型的伤害的攻击/防御上限
            对判定类攻击,通过记录有第几类
            
    */
    vector <lf> dam;   
    /*
      --速度因子--

     */
    vector <lf> spd;    

    //按照FGid排序
    bool operator <(const weapon &b)const{
        return FGid<b.FGid;
    }
    weapon()//初始值要预留足够的空间
    {
        dam.clear();
        spd.clear();
        //dam.resize(T+1);
        //spd.resize(T+1);
        name="";
        type=FGid=0;

    }

}w[A];
//const ll _size_weapon=sizeof(statue); //检测用,实际运用会删除

}


#endif