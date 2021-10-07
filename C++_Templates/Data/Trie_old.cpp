#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<Data/Tstack.h>
using namespace std;
typedef long long ll;



typedef size_t value;

class Trie{
    private:
    //½áµã node
    struct node{
        array <size_t,26> _A;
        value *val;
        size_t &operator [](const size_t &_X){
            return _A[_X];
        }
        size_t  operator [](const size_t &_X)const{
            return _A[_X];
        }
        node()
        {
            _A.fill(0);
            val=NULL;
        }
    };
    /**
     * @brief EZ allocate vector.
     * It can recycle unused element.
     * 
     */
    struct autovector{
        vector <node> vec;//The actual vector.
        Tstack  <size_t> q;//To recycle unused node
        node& operator [](const size_t &_X){
            return vec[_X];
        }
        node  operator [](const size_t &_X)const{
            return vec[_X];
        }
        void allocate(const size_t &_X,const size_t &_to)
        {
            if(q.empty())
            {
                if(vec.empty()) //Start to reserve 
                    vec.resize(2);//Reserve at least 2
                else vec.resize(vec.size()+1);//Just add 1
               // cout << vec.size()-1 << "Size" <<endl;
                vec[_X][_to]=vec.size()-1;
            }
            else{ //Recycle the remaining element 
                size_t x=q.front();
                q.pop();
                vec[_X][_to]=x;
            }
        }

        //Behaviors like vector


        void reserve(const size_t &_X)
        {
            if(vec.capacity()+q.size()<_X) 
                vec.reserve(_X-q.size()); 
        }
    
    
    }nxt;
    
    public:
    /**
     * @brief 
     * 
     * @param _str The string inserted.
     * @param _val The value attached
     */
    void insert(const char *_str,const value &_val)
    {
        size_t j=0;//node number from the root 0
        for(  ; *_str ; ++_str )//ÔìTrieÊ÷
        {
            int x=*_str-'a';
            if(x>25||x<0) return ;//´íÎó!
            if(!nxt[j][x])  nxt.allocate(j,x);
            j=nxt[j][x];//Ìøj
        }
        nxt[j].val =  new value;
        *nxt[j].val = _val;
    }
     
    /**
     * @brief 
     * 
     * @param _str The string to find its value.
     */
    size_t find(const char *_str)
    {
        size_t j=0;//node number from the root 0
        for(  ; *_str ; ++_str )//ÔìTrieÊ÷
        {
            int x=*_str-'a';
            if(x>25||x<0) return 0;//´íÎó!
            if(!nxt[j][x])  return 0;
            j=nxt[j][x];//Ìøj
        }
        return *nxt[j].val;
    }
   
    /**
     * @brief Reserve a certain number of chars.
     * 
     * @param _X The char numbers.
     */
    void reserve(const size_t &_X)
    {
        nxt.reserve(_X+1);
    }
    /**
     * @brief 
     * Print out the Trie in breadth first order.
    
    void print()
    {
        queue <size_t> q;
        q.push(0);
        while(!q.empty())
        {
            auto x=q.front();
            cout << x << ": ";
            for(auto i:nxt[x]._A)
                if(i) 
                {
                    cout << i << " ";
                    q.push(i);
                }
            cout << endl;
            q.pop();
        }
    }
     */

    void erase(const char *_str)
    {
        size_t j=0;//node number from the root 0
        for(  ; *_str ; ++_str )//Make Trie Tree.
        {
            int x=*_str-'a';
            if(x>25||x<0) return ;//Error
            if(!nxt[j][x])  return;
            j=nxt[j][x];//Jump to nxt
        }
        if(nxt[j].val!=NULL) return ;
        
    }
    
    /**
     * @brief Construct a new Trie object
     * Initial with 2 node.
     * The root node value is 0.
     */
    Trie()
    {
       nxt.vec.resize(1); 
    }

}v;



int main()
{
    
    return 0;
}