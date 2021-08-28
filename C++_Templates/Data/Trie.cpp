// 这是字典树写在函数里面的
// 匹配每个出现了几次
// 复杂度O(每个字符串的最长长度 + 文本长度)
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<Data/Tstack.h>
using namespace std;
typedef long long ll;
const ll N=2e5+10;
const ll M=2e6+10;




class Trie{
    private:
    //结点 node
    struct node{
        array <size_t,26> _A;
        size_t id;
        size_t &operator [](const size_t &_X){
            return _A[_X];
        }
        size_t  operator [](const size_t &_X)const{
            return _A[_X];
        }
        node()
        {
            _A.fill(0);
            id=0;
        }

    };
    //自动化数组 自动申请/删除
    struct autovector{
        vector <node> vec;//The actual vector.
        Tstack  <size_t> q;//To recycle unused node
        node& operator [](const size_t &_X){
            return vec[_X];
        }
        node  operator [](const size_t &_X)const{
            return vec[_X];
        }
        size_t allocate()
        {
            if(q.empty())
            {
                if(vec.empty()) //Start to reserve 
                    vec.resize(2);//Reserve at least 2
                else vec.resize(vec.size()+1);//Just add 1
                cout << vec.size()-1 << "Size" <<endl;
                return vec.size()-1;//The last element.
            }
            else{ //Recycle the remaining element 
                size_t x=q.front();
                q.pop();
                return x;//the recycled element.
            }
        }

        //Behaviors like vector


        void reserve(const size_t &_X)
        {
            if(vec.capacity()+q.size()<_X) 
                vec.reserve(_X-q.size()); 
        }
    
    
    }v;
    
    public:
    /**
     * @brief 
     * 
     * @param _str The string inserted.
     * @param num 
     */
    void insert(const char *_str,const int &num)
    {
        size_t j=0;//node number from the root 0
        for(  ; *_str ; ++_str )//造Trie树
        {
            int x=*_str-'a';
            if(x>25||x<0) return ;//错误!
            if(!v[j][x]) {j=v.allocate();cout << (v[j][x]=j) << endl;}//开节点
            j=v[j][x];//跳j
        }
        v[j].id=num;
    }
    size_t find(const char *_str)
    {
        size_t j=0;//node number from the root 0
        for(  ; *_str ; ++_str )//造Trie树
        {
            int x=*_str-'a';
            if(x>25||x<0) return 0;//错误!
            if(!v[j][x])  return 0;
            j=v[j][x];//跳j
        }
        return v[j].id;
    }
   
    /**
     * @brief Reserve a certain number of chars.
     * 
     * @param _X The char numbers.
     */
    void reserve(const size_t &_X)
    {
        v.reserve(_X+1);
    }
    
    /**
     * @brief Construct a new Trie object
     * Initial with 2 node.
     * The root node id is 0.
     */
    Trie()
    {
       v.vec.resize(1); 
    }

}v;




int main()
{
    int n;
    string str;
    while(cin >> n >> str)
    {            

        if(n) v.insert(str.c_str(),n);
        else cout << v.find(str.c_str()) <<endl;
    }

    return 0;
}