#include <bits/stdc++.h>



std::set <std::string> names;

template<typename T>                            //������ʵ�Σ���ӵ�ȫ�����ݽṹ��
void logAndAddImpl(T&& name, std::false_type t)	//����ע������std::false_type
{
    // auto now = std::chrono::system_clock::now();
    // log(now, "logAndAdd");
    names.emplace(std::forward<T>(name));
}

void logAndAddImpl(int idx, std::true_type t);


template<typename T>
void logAndAdd(T&& name)
{
    logAndAddImpl(
        std::forward<T>(name),
        std::is_integral<typename std::remove_reference_t<T>>()
    );
}

std::string nameFromIdx(int idx) { return "string";}           //������26һ��������ʵ�Σ��������ֲ���������logAndAdd
void logAndAddImpl(int idx, std::true_type t) //����ע������std::true_type
{
    logAndAdd(nameFromIdx(idx)); 
}

signed main() {
    logAndAdd(1);
    logAndAdd(std::string("str"));
    const char *ptr = "nullptr";
    std::cout << strlen(ptr);
    return 0;
}