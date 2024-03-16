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
            tmp = re[i-1][j];         //�ݴ�re[i-1][j]
            re[i][j] = tmp + re[i][j];//�ӷ�
            re[i-1][j]=0;               //�ӷ���ͬʱԭ����ʧ
            re[i-1][j] =tmp;          //���ݴ���ֵ�ֵ��¼��
        }
    //todo
    Print();
    //Second Step:Carry
    for (int j = 5; j >= 1; --j) //δ���
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
            tmp = re[i-1][j];         //�ݴ�re[i-1][j]
            re[i][j] = tmp + re[i][j];//�ӷ�
            re[i-1][j]=0;               //�ӷ���ͬʱԭ����ʧ
            re[i-1][j] =tmp;          //���ݴ���ֵ�ֵ��¼��
        }
    
    //todo
    Print();
    //Fourth Step:Carry
    for (int j = 5; j >= 1; --j) //δ���
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