#ifndef __FG_BASIC_
#define __FG_BASIC_
#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ul;
typedef double lf;
typedef unsigned int ui;
using namespace std;

/**
 * @brief FingerGlory �����ռ�
 * ��ֹ��ٰ���
 */
namespace FG{
const ll T=4;//������������
const ll A=101;//��������


struct weapon{
    string name;    //����
    ui FGid;        //FingerGlory ID
    ui type;        //��������
    lf dam[T+1];    //�˺�����
    lf spd[T+1];    //��������
    
    

    bool operator <(const weapon &b)const{
        return FGid<b.FGid;
    }

}w[A];


}


#endif