#ifndef __FG_BASIC_
#define __FG_BASIC_
#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ul;
typedef double lf;
typedef unsigned int ui;
using namespace std;

/**
 * @brief FingerGlory 命名空间
 * 防止误操包括
 */
namespace FG{
const ll T=4;//武器属性总量
const ll A=101;//武器总数


struct weapon{
    string name;    //名字
    ui FGid;        //FingerGlory ID
    ui type;        //操作种类
    lf dam[T+1];    //伤害属性
    lf spd[T+1];    //速率因数
    
    

    bool operator <(const weapon &b)const{
        return FGid<b.FGid;
    }

}w[A];


}


#endif