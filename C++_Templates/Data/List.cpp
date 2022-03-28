#ifndef __DATA_LIST_H__
#define __DATA_LIST_H__
//#include <bits/allocator.h>
#include <vector>

namespace dark{

typedef unsigned long long value_type ; //Test use
/**
 * @brief A %List of DarkSharpness.
 * Easy to use.
 * Based on std::vector.
 * 
 * @tparam value_type The value in the list. 
 */
//template <typename value_type>
class List{

/* 
Map of %List: 
    1.Declaration and Defines
    2.Functions
    3.Iterators
    4.Realizations
    5.Initailization and Delete
 */


    //Structs and Classes
    protected:

    struct  node;                        //Element carrier
    struct  Tallocator;                  //Personalized allocator
    class   iterator;                    //Personalized iterator
    class   const_iterator;              //Personalized c_iterator





    //Defines


    typedef node* nodeptr;                      //Nodepointers   definer
    typedef const node* const_nodeptr;          //C_nodepointers definer
    typedef const value_type& const_reference;  //C_reference to value_t
    #define null (nodeptr)emptynode
    #define head emptynode[1]
    #define tail emptynode[0]



    //Functions
    public:

    /**
     * @brief Push an element to the front in O(1).
     * 
     * @param _V Element's value.
     */
    void push_front(const_reference _V){
        nodeptr oldhead=head;
        head=oldhead->prv=A.apply();
        head->prv=null;
        head->nxt=oldhead;
        head->val=_V;
        (null)->nxt=head;
        //Also works when it is empty!
    }
    /**
     * @brief Push an element to the back in O(1).
     * 
     * @param _V Element's value.
     */
    void push_back(const_reference _V){    
        nodeptr oldtail=tail;
        tail=oldtail->nxt=A.apply();
        tail->nxt=null;
        tail->prv=oldtail;
        tail->val=_V;
        (null)->prv=tail;
        //Also works when it is empty!
    }
    /**
     * @brief Pop out the element SAFELY in the back in O(1).
     * Note that no element is returned.\n 
     * If you do need it , get it before it is poped
     * OR access recent() before any other 
     * operation is done to the %List.
     * 
     */
    void pop_back(){
        if(tail==null) return;
        A.recycle(tail);
        tail=tail->prv;
        tail->nxt=null;
    }
    /**
     * @brief Pop out the element SAFELY in the front in O(1).
     * Note that no element is returned.\n 
     * If you do need it , get it before it is poped
     * OR access recent() before any other 
     * operation is done to the %List.
     * 
     */
    void pop_front(){
        if(head==null) return;
        A.recycle(head);
        head=head->nxt;
        head->prv=null;
    }
    
    
    //Return the size recorded in O(1).
    size_t size()const{
        return A.size;
    }
    //Actually,I don't find it any use. O(1) .
    size_t maxsize()const{
        return size_t(-1)/(sizeof(value_type)+(sizeof(nodeptr)<<1));
    }
    
    /**
     * @brief Clear the nodes in O(n).
     * These nodes will be moved to the vector.
     */
    void clear(){
        nodeptr tmp=head;
        while(tmp!=tail){
            vector.

        }
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
    /**
     * @brief Return the last element poped.
     * Use it before any other operations,
     * or it cannot give you the right element.\n 
     * 
     * You may use it to retrieve the element
     * that has just been poped.
     * 
     * @return The last element poped in O(1).
     */
    value_type recent(){
        return A.v.back()->val;
    }
    
    /**
     * @brief 
     * 
     * @param _L The second %List to be attached to the back.
     * Note that the data of the second %List will be merged,
     * which means it will be emptied,with its unused nodes
     * untouched as well.
     * O(1) operation.
     */
    void merge_back (List& _L){
        tail->nxt=_L.head;
        (_L.head)->prv=tail;
        tail=_L.tail;
        tail->nxt=null;
        _L.head=_L.tail=(nodeptr)_L.emptynode;//Clear
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
        return null;
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
        return null;
    }


    //Classes 
    protected:

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
            //ptr==NULL;
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
            //ptr=NULL;
        }
    };

   
    //Structs
    protected:
    
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
        //protected:
        nodeptr prv;   //The previous element.
        nodeptr nxt;   //The   next   element.
        public:
        value_type val;//Recorder  of  value .
        //do sth.
        node(){
            prv=nxt=NULL;
        }
    }*emptynode[2]; 
    //Work as ptr to emptynode.Also as head/tail ptr;
    
    
    //Ending
    public:
    List(){
        head=tail=null;
    }
    ~List(){
        nodeptr ptr=head,tmp;
        while(ptr!=null){
            tmp=ptr->nxt;
            A.deallocate(ptr,1);
            ptr=tmp;
        }
    }


    #undef null
    #undef head
    #undef tail
};//Size=48
//const int x=sizeof(List);
   
}

#endif