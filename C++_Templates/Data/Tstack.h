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
        node *top; //顶部指针
        node *tmp; //临时指针
        allocator<node> a;
    public:
    //顶部添加元素
    inline void push(const key &x)
    {
        tmp=top;
        top=a.allocate(1);
        top->c=tmp;
        top->val=x;
    }
    //如果空了那么就不会清空
    inline void pop(){
        if(top==NULL) return ;
        tmp=top->c;
        a.deallocate(top,1);
        top=tmp;
    }
    //返回顶部值(常数)
    inline key front()const{
        if(top==NULL) 
        {
            throw "no data" ;
       }
        else return top->val;
    }
    //返回顶部值(引用)
    inline key& front(){
        if(top==NULL) 
        {
            throw "no data" ;
       }
        else return top->val;
    }
    //返回顶部值并弹出这个数
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
    //如果头指针为空就是空
    inline bool empty()const{
        return top==NULL ? true:false;
    }
    //头指针初始为空
    inline Tstack()
    {
        top=NULL;
    }
};


}
#endif