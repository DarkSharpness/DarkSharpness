//A space costing Trie for small 
//capitalized numbers.
//Suitable for small amount of data.
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef size_t value;
//Sizeof 232
//template <typename value>
class xTrie{

    private:

    class iter;
    struct node {
        node * head;//father
        array <node*,26> _A;
        value * vptr; //pointer to the value
        inline node*&  operator[](const size_t &_loc){
            return _A[_loc];
        }
        inline node*   operator[](const size_t &_loc)const{
            return _A[_loc];
        }
        inline node() {
            vptr=NULL;
            head=NULL;
            _A.fill(NULL);
        }
    }_root;//root of the Trie.
    

    allocator <node>  N;//node  allocator.
    allocator <value> V;//value allocator.
    //char c;
    public:
    
    /**
     * @brief Insert a string into the %Trie. \n 
     * Check if it is a standard string ,
     * ending by '' before insert.
     * 
     * @param _str String inserted.
     * @param _val Value  attached.
     */
    inline void insert(const char *_str,const value &_val)
    {
        if(*_str == 0 ) return ;
        node *tmp = &_root;
        size_t _ch;
        while(*_str!=0)
        { 
            if(*_str<'a'||*_str>'z') return;
            _ch=*_str-'a';
            if( (*tmp)[_ch]==NULL)
            {
                (*tmp)[_ch]=N.allocate(1);
                (*tmp)[_ch]->head=tmp;
                tmp=(*tmp)[_ch];
            }
            else tmp=(*tmp)[_ch];
            ++_str;
        }
        tmp->vptr=V.allocate(1);//ptr to a new address.
        *tmp->vptr=_val;        //copy the data
    }

    inline iter find(char* _str)const
    {
        const node *tmp = &_root;//from the root
        if(*_str == 0 ) goto Nothing ; //empty string
        int _ch;//char id
        while(*_str != 0) //while not reaching the end
        { 
            if(*_str<'a'||*_str>'z') goto Nothing;//illegal
            _ch=*_str-'a';          //'a~z' -> 0~25
            if( (*tmp)[_ch]==NULL)   goto Nothing;//end in advance
            tmp=(*tmp)[_ch];        //go on
            ++_str;                 //go on
        }
        if(tmp->vptr==NULL) goto Nothing;//no value.
        return const iter(tmp);//
        Nothing://returns the root.
        return const iter(&_root);
        ;
    }


//Assistant iterator.
    class iter{
        node * ptr;
        public:
        //Initialize with a given ptr
        
        iter(){

        }
        inline iter operator ++(void){
            
        }
        inline value& operator *(void){
            return *(ptr->vptr);
        }
        inline value  operator *(void)const{
            return *(ptr->vptr);
        }
    };
        

    xTrie()
    {

    }
};
//xTrie::iter x;
const int X=sizeof(xTrie);

int main()
{
    
    return 0;
}