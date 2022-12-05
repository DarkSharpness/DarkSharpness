//�����Լ�����һЩȫ�ֱ���������ͷ�ļ�
#include <bits/stdc++.h>

inline bool checkChar(char ch) {
    return (ch >= 'a' && ch <= 'z') ||
           (ch >= 'A' && ch <= 'Z');
}


enum pokeType {
    fire,
    water,
    grass,
    electric,
    flying,
    ground,
    dragon
};

class BasicException {
protected:
    std::string message;
public:
    explicit BasicException(const std::string & _message) {
        message = _message;
    }

    virtual std::string what() const {
        return message;
    }
    BasicException()  = default;
    ~BasicException() = default;
};

class ArgumentException: public BasicException {
  public:
    ArgumentException(const std::string &word) : BasicException(word) {}
};

class IteratorException: public BasicException {
  public:
    IteratorException(const std::string &word) : BasicException(word) {}
};

struct Pokemon {
    char name[12];
    int id;
    std::bitset <7> type;
    Pokemon() {
        id = 0;
        memset(name,0,sizeof(name));
    }
    inline bool operator <(const Pokemon &p) {return id < p.id;}

};

int getType(const std::string &name) {
    if(name == "fire")     return fire;
    if(name == "water")    return fire;
    if(name == "grass")    return grass;
    if(name == "electric") return electric;
    if(name == "flying")   return flying;
    if(name == "ground")   return ground;
    if(name == "dragon")   return dragon;
    throw ArgumentException(
        "Argument Error: PM Type Invalid ("
        + name
        + ')'
    );
}

void checkName(Pokemon &tmp,const char *name) {
    int len = strlen(name);
    for(int i = 0 ; i < len ; ++i) {
        if(!checkChar(name[i])) {
            throw ArgumentException(
                "Argument Error: PM Name Invalid ("
                + std::string(name)
                + ')'
            );
        }
    }
    strcpy(tmp.name,name);
}

void checkID(Pokemon &tmp,int id) {
    if(id <= 0) {
        throw ArgumentException(
            "Argument Error: PM ID Invalid ("
            + std::to_string(id)   
            + ')'
        );
    }
    tmp.id = id;
}


void checkType(Pokemon &tmp,const char *types) {
    std::string name;
    int len = strlen(types);
    for(int i = 0 ; i < len ; ++i) {
        if(types[i] != '#') {
            name.push_back(types[i]);
        } else {
            tmp.type.set(getType(name));
            name.clear();
        }
    }
}


class Pokedex {
private:
    //�����Լ�������Ҫ�ĳ�Ա
    std::fstream File;
    std::string  FileName;
    std::set <Pokemon> set;
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
    explicit Pokedex(const std::string &_fileName) {
        FileName = _fileName;
        File.open(_fileName);
        if(!File.good()) {
            File.open(_fileName,std::ios::out);
            File.close();
        } else {
            Pokemon tmp;
            File.seekg(0);
            while(!File.eof()) {
                File.read(reinterpret_cast <char *>(&tmp),sizeof(Pokemon));
                set.insert(tmp);
            }
            File.close();
        }
  
    }

    ~Pokedex() {
        File.open(FileName);
        for(auto &tmp : set) {
            File.write(reinterpret_cast <const char *>(&tmp),sizeof(Pokemon));
        }
        File.close();
    }

    bool pokeAdd(const char *name, int id, const char *types) {
        Pokemon ans;

        checkName(ans,name);
        checkID(ans,id);
        checkType(ans,types);

        return set.insert(ans).second;
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