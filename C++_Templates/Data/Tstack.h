//Stack for Treap Algorithm
//Easy to use,and require less space than required
//Do not use it unless necessary.

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
    class Tstack{
        struct node
        {
            key val;
            node *c;
        };
        node *top; //顶部指针
        node *tmp; //临时指针
        size_t siz;
        allocator <node> a;
    public:
    //Add element to the top of the stack.
    inline void push(const key &x)
    {
        tmp=top;
        top=a.allocate(1);
        top->c=tmp;
        top->val=x;
        ++siz;
    }
    //Pop the top element.If the stack is empty,nothing happens.
    inline void pop(){
        if(top==NULL) return ;
        --siz;
        tmp=top->c;
        a.deallocate(top,1);
        top=tmp;
    }
    //Read only reference to the top element.
    inline key front()const{
        if(top==NULL) 
        {
            throw "no data" ;
       }
        else return top->val;
    }
    //The siz of the stack.
    inline size_t size()const{
        return siz;
    }
    //Read/Write reference to the top element.
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
            --siz;
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
        siz=0;
    }
    };

}
#endif