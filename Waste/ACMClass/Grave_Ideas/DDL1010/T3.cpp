#include <iostream>
using namespace std;

int re[9][6];
bool overflow[9] = {  false,
    false,false,false,false,
    false,false,false,false
};



void Print() {
    for (int j = 1; j <= 5; ++j) {
        for (int i = 8; i >= 1; --i) {
            cout << re[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    for (int j = 1; j <= 5; ++j)
        for (int i = 8; i >= 1; --i)
            cin >> re[i][j];
    //First Step:Add
    for (int j = 1; j <= 5; ++j) 
        for (int i = 8; i >= 1; i -= 2) {
            int tmp;
            tmp = re[i-1][j];         //暂存re[i-1][j]
            re[i][j] = tmp + re[i][j];//加法
            re[i-1][j]=0;               //加法的同时原数消失
            re[i-1][j] =tmp;          //把暂存齿轮的值刻录回
        }
    //todo
    Print();
    //Second Step:Carry
    for (int j = 5; j >= 1; --j) //未溢出
        for (int i = 8; i >= 1; i -= 2) {
            if(re[i][j] >= 10) {
                ++re[i][j-1];
                re[i][j] -=10;
            }
        }
    for(int i = 8 ; i >= 1; i -= 2)
        if(re[i][0]) overflow[i] = true;
    //todo
    Print();
    //Third Step:Add
    for (int j = 1; j <= 5; ++j) 
        for (int i = 7; i >= 1; i -= 2) {
            int tmp;
            tmp = re[i-1][j];         //暂存re[i-1][j]
            re[i][j] = tmp + re[i][j];//加法
            re[i-1][j]=0;               //加法的同时原数消失
            re[i-1][j] =tmp;          //把暂存齿轮的值刻录回
        }
    
    //todo
    Print();
    //Fourth Step:Carry
    for (int j = 5; j >= 1; --j) //未溢出
        for (int i = 7; i >= 1; i -= 2) {
            if(re[i][j] >= 10) {
                ++re[i][j-1];
                re[i][j] -=10;
            }
        }
    for(int i = 7 ; i >= 1; i -= 2)
        if(re[i][0]) overflow[i] = true;
    
    //todo
    Print();
}