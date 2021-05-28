#ifndef _Data_T_Stack_
#define _Data_T_Stack_
#include <bits/allocator.h>
//typedef int key;


namespace std
{
    /**
     * @brief A space-saving and simple stack.
     * 
     */
    template <typename key>
    class Tstack
    {
        struct node
        {
            key val;
            node *c;
        };
        node *top; //����ָ��
        node *tmp; //��ʱָ��
        allocator<node> a;
    public:
    //�������Ԫ��
    inline void push(const key &x)
    {
        tmp=top;
        top=a.allocate(1);
        top->c=tmp;
        top->val=x;
    }
    //���������ô�Ͳ������
    inline void pop(){
        if(top==NULL) return ;
        tmp=top->c;
        a.deallocate(top,1);
        top=tmp;
    }
    //���ض���ֵ(����)
    inline key front()const{
        if(top==NULL) 
        {
            throw "no data" ;
       }
        else return top->val;
    }
    //���ض���ֵ(����)
    inline key& front(){
        if(top==NULL) 
        {
            throw "no data" ;
       }
        else return top->val;
    }
    //���ض���ֵ�����������
    inline key popfront(){
        if(top==NULL) throw "Out of range";
        else 
        {
            key v=top->val;
            tmp=top->c;
            a.deallocate(top,1);
            top=tmp;
            return v;
        }
    }
    //���ͷָ��Ϊ�վ��ǿ�
    inline bool empty()const{
        return top==NULL ? true:false;
    }
    //ͷָ���ʼΪ��
    inline Tstack()
    {
        top=NULL;
    }
};


}
#endif