#ifndef __FG_BASIC_
#define __FG_BASIC_
#include <DarkSharpness/FG/Fmath.h>
#include <DarkSharpness/C++_Templates/statue.h>

/**
 * @brief FingerGlory �����ռ�
 * ��ֹ���
 */
namespace FG{


//��Щ�����Ժ��������
const ll T=5   ;//������������
const ll A=101 ;//��������


//״̬��¼




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
    //��¼��Ӧ�����ļ�λ
    statue <96> st;
    /*
        --�˺�������--
        �±�0���Ǽ�¼������:
            ����ǹ�����,��¼����Ŀ������,���=0����Ⱥ�� =-1���ж�Ⱥ��
            ����Ƿ�����,������¼����ʲô��
                2^1 �շ���(�з�������)
                2^2 ������(����������)
                2^3 ������(FG����)
            ����ǵ���,��¼��������.���<0,�����Ա���.
        �±�i(i>0) 
            type=1,2�ż�
            ��¼ʲô���͵��˺��Ĺ���/��������
            ���ж��๥��,ͨ����¼�еڼ���
            
    */
    vector <lf> dam;   
    /*
      --�ٶ�����--

     */
    vector <lf> spd;    

    //����FGid����
    bool operator <(const weapon &b)const{
        return FGid<b.FGid;
    }
    weapon()//��ʼֵҪԤ���㹻�Ŀռ�
    {
        dam.clear();
        spd.clear();
        //dam.resize(T+1);
        //spd.resize(T+1);
        name="";
        type=FGid=0;

    }

}w[A];
//const ll _size_weapon=sizeof(statue); //�����,ʵ�����û�ɾ��

}


#endif