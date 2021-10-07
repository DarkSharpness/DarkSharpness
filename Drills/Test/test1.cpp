#include<bits/stdc++.h>
#include<Data/Tstack.h>
using namespace std;
typedef long long ll;
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
            // cout << vec.size()-1 << "Size" <<endl;
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

int main()
{
    v.vec.resize(2);
    cin >> v[1][1];
    system("pause");
    cout << v[1][1]<< endl;
    return 0;
}