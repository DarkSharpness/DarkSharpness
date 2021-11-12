//Abadoned
#if __cplusplus < 0L 

//Stack for Tree Algorithm
//Easy to use,and require less space than required
//Do not use it unless necessary.

#ifndef _Data_T_Stack_
#define _Data_T_Stack_
#include <bits/allocator.h>
//typedef int key;


namespace dks
{

    /**
     * @brief A space-saving and simple stack.\n 
     * Sizeof : 8/16 Byte.
     */
    template <typename key>
class Tstack{
    struct node{
        key val;
        node *c;
    } *top;//∂•≤ø÷∏’Î
    struct T_allocator : allocator <node>{
        size_t siz;
    }a;


    public:
    //Iterator related.
    class iterator{
        private: 
        node *ptr;
        public:
        void operator ++(){
            ptr=ptr->c;
        }
        iterator(node *_ptr){
            ptr=_ptr;
        }
    };
    class const_iterator{
        private: 
        const node *ptr;
        public:
        void operator ++(){
            ptr=ptr->c;
        }
        const_iterator(const node *_ptr){
            ptr=_ptr;
        }
    };
    inline iterator begin(){
        return iterator(top);
    }
    inline iterator end(){
        return iterator(NULL);
    }
    inline const_iterator cbegin()const{
        return const_iterator(top);
    }
    inline const_iterator cend(){
        return const_iterator(NULL);
    }




    //Add element to the top of the stack.
    inline void push(const key &x){
        node * tmp=top;
        top=a.allocate(1);
        top->c=tmp;
        top->val=x;
        ++a.siz;
    }
    
    //Pop the top element.If the stack is empty,nothing happens.
    inline void pop(){
        if(top==NULL) return ;
        --a.siz;
        node * tmp=top->c;
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
    
    //The size of the stack.
    inline size_t size()const{
        return a.siz;
    }
    
    //Read/Write reference to the top element.
    inline key& front(){
        if(top==NULL) 
        {
            throw "no data" ;
        }
        else return top->val;
    }
    
    //Return the top element and pop it out.
    inline key popfront(){
        if(top==NULL) throw "Out of range";
        else 
        {
            --a.siz;
            key v=top->val;
            node * tmp=top->c;
            a.deallocate(top,1);
            top=tmp;
            return v;
        }
}

    //Test if the stack is empty.
    inline bool empty()const{
        return top==NULL ;//? true:false;
    }
    
    //Test if the stack is not empty.
    inline bool nempty()const{
        return top!=NULL ;//? true:false;
    }
    
    //Initialize.
    Tstack(){
        top=NULL;
        a.siz=0;
    }
    //Clear the data.
    ~Tstack(){
        while(top!=NULL) pop();
        //cout << "fuck" <<endl;
    }
};

//const size_t _X=sizeof(Tstack<int>);
//size : 16

}


#endif


#endif