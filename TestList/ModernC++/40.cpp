#include <bits/stdc++.h>

signed main() {

    std::atomic <int> ai(0);         //��ʼ��aiΪ0
    ai = 10;                        //ԭ���Ե�����aiΪ10
    std::cout << ai;                //ԭ���Եض�ȡai��ֵ
    ++ai;                           //ԭ���Եص���ai��11
    --ai;                           //ԭ���Եصݼ�ai��10

    return 0;
}