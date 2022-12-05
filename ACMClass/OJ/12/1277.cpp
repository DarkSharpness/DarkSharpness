//可以自己定义一些全局变量、引用头文件
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
    //可以自己定义需要的成员
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
        //TO DO: 删除对应宝可梦
        //return: 返回是否删除成功
    }

    std::string pokeFind(int id) const {
        //TO DO: 查询id对应的宝可梦
        //return: 如果找到，返回宝可梦的name。否则返回字符串 "None"
    }

    std::string typeFind(const char *types) const {
        //TO DO: 查询属性包含了types中的属性的宝可梦
        //return: 如果找到，返回多行字符串。第一行为满足的宝可梦数量，
        //          接下来每一行为宝可梦的name，按id从小到大。
        //        如果找不到，返回字符串 "None"
        //注意，types可能为多种属性，同样用 # 号分隔
    }

    double attack(const char *type, int id) const {
        //TO DO: 伤害倍率计算
        //return: 返回id对应的宝可梦受到属性type的攻击的伤害倍率。
        //          如果id对应不存在宝可梦，返回 -1
        //这里type保证为单属性
    }

    int catchTry() const {
        //TO DO: 全图鉴捕获尝试
        //return: 按照前文过程最后能拥有的宝可梦数量。
    }

    struct iterator {
        //可以自己定义所需要的成员

        iterator &operator++() {
            //TO DO: ++迭代器
        }
        iterator &operator--() {
            //TO DO: --迭代器
        }
        iterator operator++(int) {
            //TO DO: 迭代器++
        }
        iterator operator--(int) {
            //TO DO: 迭代器--
        }
        iterator & operator = (const iterator &rhs) {
            //TO DO: 迭代器赋值
        }
        bool operator == (const iterator &rhs) const {
            //TO DO: 判断迭代器是否指向同一位置
        }
        bool operator != (const iterator &rhs) const {
            //TO DO: 不等号
        }
        Pokemon & operator*() const {
            //TO DO: * 运算符
        }
        /**
         * for the support of it->first.
         * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
         */
        Pokemon * operator->() const {
            //TO DO: -> 运算符
        }
    };

    iterator begin() {
        //return: 返回指向图鉴头部的迭代器
    }

    iterator end() {
        //return: 返回指向图鉴尾部的迭代器。
        //准确的说，是“最后的一个元素”的后面，指向的内容为空，详情可以去了解标准库容器的 end()
    }
};