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
 * @brief FingerGlory �����ռ�
 * ��ֹ���
 */
namespace FG{


//��Щ�����Ժ��������
const ll T=5   ;//������������
const ll A=101 ;//��������

/**
 * @brief �����ṹ��
 * @param name ����
 * @param FGid FG�����ID
 * @param type ��������
 * @param dam �˺�������
 * @param spd �ٶ�����
 */
struct weapon{
    string name;    //����
    ui FGid;        //FingerGlory ID
    
   
    /*
      --type ���Ͳ���--
      �ڱ�׼FG�� 
      1,�ǹ�����
      2,�Ƿ�����
      3,�ǵ���
      4,�Ǽ�����
     */
    ch type;
    /*
        --�˺�������--
        �ڱ�׼FG��
        �±�0���Ǽ�¼������:
            ����ǹ�����,��¼����Ŀ������,���=0����Ⱥ��
            ����Ƿ�����,������¼����Ŀ��
    */
    vector <lf> dam;    
    vector <lf> spd;    //��������
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