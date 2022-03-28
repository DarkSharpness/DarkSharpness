#include<bits/stdc++.h>

namespace dark{

class numstr{
    typedef const numstr& c_refer;
    #define _X (*this)



    std::vector<char> num; 
    //num[0] sign: 0 positive , 1 negative 
    
    //Remove unnecessary 0 in the back
    inline void remove_0(){
        while(!num.empty()||num.back()=='0') num.pop_back();
        if(num.empty()) num.push_back('0');
    }


    public:
    inline bool operator==(c_refer _Y )const{
        return num == _Y.num;
    }
    inline numstr operator+(c_refer _Y )const{
        int tmp = 0;
        
    }


    //print out the number
    void print(){
        for(auto iter=num.rbegin() ; 
            iter!= num.rend() ; ++iter  ) 
                putchar(*iter);
    }

    numstr(){
        
    }
};

}

int main()
{

    return 0;
}