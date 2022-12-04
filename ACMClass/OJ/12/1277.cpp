//�����Լ�����һЩȫ�ֱ���������ͷ�ļ�
#include <bits/stdc++.h>

class BasicException {
protected:
    std::string message;
public:
    explicit BasicException(const char *_message) {
        message = _message;
    }

    virtual const char *what() const {
        //return: ������Ϣ�ַ���
        return message.c_str();
    }
    BasicException()  = default;
    ~BasicException() = default;
};

class ArgumentException: public BasicException {
  public:
    ArgumentException(const char *word) : BasicException(word) {}
};

class IteratorException: public BasicException {
  public:
    IteratorException(const char *word) : BasicException(word) {}
};

struct Pokemon {
    char name[12];
    int id;
    int type[7];
    Pokemon() {
        memset(name,0,sizeof(name));
        memset(type,0,sizeof(type));
        id = 0;
    }


    //...
};

class Pokedex {
private:
    //�����Լ�������Ҫ�ĳ�Ա
    std::fstream File;
    std::string  FileName;

    static constexpr double atkMap[7][7] =
    {
        0.5,0.5, 2 , 1 , 1 , 1 ,0.5,
         2 ,0.5,0.5, 1 , 1 , 2 ,0.5,
        0.5, 2 ,0.5, 1 ,0.5, 2 ,0.5,
         1 , 2 ,0.5, 1 , 2 , 0 ,0.5,
         1 , 1 , 2 ,0.5, 1 , 1 , 1 ,
         2 , 1 ,0.5, 2 , 0 , 1 , 1 ,
         1 , 1 , 1 , 1 , 1 , 1 , 2 ,
    };

public:
    explicit Pokedex(const char *_fileName) {
        FileName = _fileName;
        File.open(_fileName);
        if(!File.good()) {

        }

        File.close();
    }

    ~Pokedex() {
        //TO DO: ��������
    }

    bool pokeAdd(const char *name, int id, const char *types) {
        //TO DO: ��ӱ�����
        //�����Ƿ���ӳɹ�
    }

    bool pokeDel(int id) {
        //TO DO: ɾ����Ӧ������
        //return: �����Ƿ�ɾ���ɹ�
    }

    std::string pokeFind(int id) const {
        //TO DO: ��ѯid��Ӧ�ı�����
        //return: ����ҵ������ر����ε�name�����򷵻��ַ��� "None"
    }

    std::string typeFind(const char *types) const {
        //TO DO: ��ѯ���԰�����types�е����Եı�����
        //return: ����ҵ������ض����ַ�������һ��Ϊ����ı�����������
        //          ������ÿһ��Ϊ�����ε�name����id��С����
        //        ����Ҳ����������ַ��� "None"
        //ע�⣬types����Ϊ�������ԣ�ͬ���� # �ŷָ�
    }

    double attack(const char *type, int id) const {
        //TO DO: �˺����ʼ���
        //return: ����id��Ӧ�ı������ܵ�����type�Ĺ������˺����ʡ�
        //          ���id��Ӧ�����ڱ����Σ����� -1
        //����type��֤Ϊ������
    }

    int catchTry() const {
        //TO DO: ȫͼ��������
        //return: ����ǰ�Ĺ��������ӵ�еı�����������
    }

    struct iterator {
        //�����Լ���������Ҫ�ĳ�Ա

        iterator &operator++() {
            //TO DO: ++������
        }
        iterator &operator--() {
            //TO DO: --������
        }
        iterator operator++(int) {
            //TO DO: ������++
        }
        iterator operator--(int) {
            //TO DO: ������--
        }
        iterator & operator = (const iterator &rhs) {
            //TO DO: ��������ֵ
        }
        bool operator == (const iterator &rhs) const {
            //TO DO: �жϵ������Ƿ�ָ��ͬһλ��
        }
        bool operator != (const iterator &rhs) const {
            //TO DO: ���Ⱥ�
        }
        Pokemon & operator*() const {
            //TO DO: * �����
        }
        /**
         * for the support of it->first.
         * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
         */
        Pokemon * operator->() const {
            //TO DO: -> �����
        }
    };

    iterator begin() {
        //return: ����ָ��ͼ��ͷ���ĵ�����
    }

    iterator end() {
        //return: ����ָ��ͼ��β���ĵ�������
        //׼ȷ��˵���ǡ�����һ��Ԫ�ء��ĺ��棬ָ�������Ϊ�գ��������ȥ�˽��׼�������� end()
    }
};