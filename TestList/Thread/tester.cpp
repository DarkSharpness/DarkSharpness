#include<iostream>
#include<thread>

using namespace std;
void proc(int &a)
{
    cout << "�������߳�,�������Ϊ" << a << endl;
    cout << "���߳�����ʾ���߳�idΪ" << this_thread::get_id()<< endl;
}
int main()
{
    cout << "�������߳�" << endl;
    int a = 9;
    thread th2(proc,ref(a));//��һ������Ϊ���������ڶ�������Ϊ�ú����ĵ�һ������������ú������ն������������д�ں��档��ʱ�߳̿�ʼִ�С�
    cout << "���߳�����ʾ���߳�idΪ" << th2.get_id() << endl;
    //�˴�ʡ�Զ��У���Ҫ�ڴ������̺߳�����join,Ӧ���ڳ������ǰjoin
    th2.join();//��ʱ���̱߳�����ֱ�����߳�ִ�н�����

    return 0;
}