#ifndef __DATA_LIST_H__
#define __DATA_LIST_H__
//#include <bits/allocator.h>
#include <vector>

namespace dks{
// typedef unsigned long long value_type ; //Test use
/**
 * @brief A %List of DarkSharpness
 * 
 * @tparam value_type The value in the list. 
 */
template <typename value_type>
class List{
    private:
    struct  node;                        //Element carrier
    struct  Tallocator;                  //Personalized allocator
    class   iterator;                    //Personalized iterator
    class   const_iterator;              //Personalized c_iterator
    typedef node* nodeptr;               //Nodepointers   definer
    typedef const node* const_nodeptr;   //C_nodepointers definer
    nodeptr head;                        //Head pointer
    nodeptr tail;                        //Tail pointer
    


    //functions
    public:

    /**
     * @brief Push an element to the front in O(1).
     * 
     * @param _V Element's value.
     */
    void push_front(const value_type &_V){
        if(head==NULL)//Empty : tail changes to head
        {
            head=tail=A.apply();
            head->prv=head->nxt=NULL;
            head->val=_V;
            return;
        }
        nodeptr oldhead=head;
        head=oldhead->prv=A.apply();
        head->prv=NULL;
        head->nxt=oldhead;
        head->val=_V;
    }
    /**
     * @brief Push an element to the back in O(1).
     * 
     * @param _V Element's value.
     */
    void push_back(const value_type &_V){
        if(tail==NULL)
        {
            head=tail=A.apply();
            head->prv=head->nxt=NULL;
            head->val=_V;
            return;
        }
        nodeptr oldtail=tail;
        tail=oldtail->nxt=A.apply();
        tail->nxt=NULL;
        tail->prv=oldtail;
        tail->val=_V;
    }
    /**
     * @brief Pop out the element in the back in O(1).
     * Note that no element is returned.\n 
     * If you do need it , get it before it is poped
     * OR access the end iterator before any other 
     * operation is done to the %List.
     * 
     */
    void pop_back(){
        if(tail==NULL) return;
        A.recycle(tail);
        //tail=tail->prv;
        if(tail==head) tail=head=NULL; //Empty
        else tail=tail->prv;           //Not empty
    }
    /**
     * @brief Pop out the element in the front in O(1).
     * Note that no element is returned.\n 
     * If you do need it , get it before it is poped
     * OR access the rend iterator before any other 
     * operation is done to the %List.
     * 
     */
    void pop_front(){
        if(head==NULL) return;
        A.recycle(head);
        //head=head->nxt;
        if(tail==head) tail=head=NULL; //Empty
        else tail=head->nxt;           //Not empty
    }
    //Return the size recorded in O(1).
    size_t size(){
        return A.size;
    }
    //Actually,I don't find it any use. O(1) .
    size_t maxsize(){
        return size_t(-1)/(sizeof(value_type)+(sizeof(nodeptr)<<1));
    }
    /**
     * @brief Shrink the vector inside in O(n) or less to save the space.\n 
     * Allocated nodes are not touched to ensure fast IO.
     * Recommended to use after lots of IOs ended by INs.\n 
     * If you demand minimized space , call "shrink_to_save".
     */
    void shrink_to_fit(){
        A.v.shrink_to_fit();
    }
    /**
     * @brief Minimize the space occupied in O(n).
     * Any unused nodes will be deleted.
     * In other words,the vector inside is completely emptied.
     */
    void shrink_to_save(){
        for(nodeptr i:A.v) A.deallocate(i,1);
        A.v.clear();
        A.v.shrink_to_fit();
        
    }
   
    //Iterator related.
    public:

    /**
     * @brief 
     * 
     * @return Iterator to the first element. 
     */
    iterator begin(){
        return head;
    }
    
    /**
     * @brief 
     * 
     * @return Iterator to one past the last element. 
     */
    iterator end(){
        return tail->nxt;
    }

    /**
     * @brief 
     * 
     * @return Const_iterator to the first element. 
     */
    const_iterator cbegin(){
        return head;
    }
    
    /**
     * @brief 
     * 
     * @return Const_iterator to one past the last element. 
     */
    const_iterator cend(){
        //If tail==NULL,it should return NULL.
        return tail==NULL? NULL : tail->nxt;
    }


    //classes 
    private:

    class  iterator{//personalized iterator
        nodeptr ptr;//ptr contained
        public:
        //value pointer
        value_type& operator*(){
            return ptr->val;
        }
        //self iteration
        void operator++(){
            ptr=ptr->nxt;
        }
        //self iteration
        void operator--(){
            ptr=ptr->prv;
        }
        //Judged by whether the ptrs are the same.
        bool operator!=(const iterator &_Y)const{
            return ptr!=_Y.ptr;
        }
        bool operator==(const iterator &_Y)const{
            return ptr==_Y.ptr;
        }
        //Change to const_iterator.
        operator const_iterator()const{
            return ptr;
        }
        iterator(nodeptr __ptr){
            ptr=__ptr;
        }
        iterator(){
            ptr==NULL;
        }
    };
    
    
    class  const_iterator{
        const_nodeptr ptr;
        public:

        //value pointer
        value_type operator*(){
            return ptr->val;
        }
        //self iteration
        void operator++(){
            ptr=ptr->nxt;
        }
        //self iteration
        void operator--(){
            ptr=ptr->prv;
        }
        //Judged by whether the ptrs are the same.
        bool operator!=(const const_iterator &_Y)const{
            return ptr!=_Y.ptr;
        }
        bool operator==(const const_iterator &_Y)const{
            return ptr==_Y.ptr;
        }
        const_iterator(const_nodeptr __ptr){
            ptr=__ptr;
        }
        const_iterator(){
            ptr=NULL;
        }
    };

   
    //structs
    private:
    
    struct Tallocator : std::allocator <node>{//personalized allocator
        size_t size;            //Record sizeof the elements
        std::vector <nodeptr> v;//Recycling container.
        //allocate one new element
        nodeptr apply(){
            ++size;
            if(!v.empty()){
                v.pop_back();
                return *v.cend();
            } 
            return allocate(1);
        }
        //reuse an element
        void recycle(nodeptr _ptr){
            size--;
            v.push_back(_ptr);
        }
        //Initializaton
        Tallocator(){
            size=0;
        }
        //Delete the data
        ~Tallocator(){//clear the ptrs in vector
            for(nodeptr _I:v) deallocate(_I,1);
            v.clear();
        }
    }A;

    struct node    {//Element in the list
        nodeptr prv;   //The previous element.
        nodeptr nxt;   //The   next   element.
        value_type val;//Recorder  of  value .
        //do sth.
        node(){
            prv=nxt=NULL;
        }
    };
    
    
    //Ending
    public:
    List(){
        head=tail=NULL;
    }
    ~List(){
        nodeptr ptr=head,tmp;
        while(ptr!=NULL)
        {tmp=ptr->nxt;A.deallocate(ptr,1);ptr=tmp;}
    }
};

//const size_t X=sizeof(List);

}


#endif