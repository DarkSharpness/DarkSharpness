#include <bits/stdc++.h>

inline bool checkChar(char ch) {
    return (ch >= 'a' && ch <= 'z') ||
           (ch >= 'A' && ch <= 'Z');
}

constexpr double atkMap[7][7] = {
    0.5,0.5, 2 , 1 , 1 , 1 ,0.5,
     2 ,0.5,0.5, 1 , 1 , 2 ,0.5,
    0.5, 2 ,0.5, 1 ,0.5, 2 ,0.5,
     1 , 2 ,0.5, 1 , 2 , 0 ,0.5,
     1 , 1 , 2 ,0.5, 1 , 1 , 1 ,
     2 , 1 ,0.5, 2 , 0 , 1 , 1 ,
     1 , 1 , 1 , 1 , 1 , 1 , 2 ,
};

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
    explicit BasicException(std::string && _message) {
        message = std::move(_message);
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
    ArgumentException(std::string &&word) : BasicException(std::move(word)) {}
};

class IteratorException: public BasicException {
  public:
    IteratorException(const std::string &word) : BasicException(word) {}
    IteratorException(std::string &&word) : BasicException(std::move(word)) {}
};

struct Pokemon {
    char name[12]; // Align
    int id;
    std::bitset <8> type;
    Pokemon() {
        id = 0;
        memset(name,0,sizeof(name));
    }
    inline bool operator <(const Pokemon &p) const{return id < p.id;}
    friend std::ostream & operator <<(std::ostream &os,const Pokemon &t) {
        os << t.name << ' ' << t.id << ' ' << t.type;
        return os;
    }

};

int getType(const std::string &name) {
    if(name == "fire")     return fire;
    if(name == "water")    return water;
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
    if(len >= 11) { // too long
        throw ArgumentException(
            "Argument Error: PM Name Invalid ("
            + std::string(name)
            + ')'
        );
    }
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
    tmp.type.set(getType(name));
    name.clear();    
}

bool judgeAtk(const Pokemon &tmp,const Pokemon &enemy) {
    double maxn = 0;
    for(int i = 0 ; i < 7 ; ++i) {
        double attack = 1.0;
        if(tmp.type[i])
            for(int j = 0 ; j < 7 ; ++j)
                if(enemy.type[j])
                    attack *= atkMap[i][j];
        if(attack > maxn) maxn = attack;
    }
    return maxn >= 1.9999;
}



class Pokedex {
private:
    //可以自己定义需要的成员
    std::fstream File;
    std::string  FileName;
    std::set <Pokemon> set;
    

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
        for(auto &it : set) {
            File.write(reinterpret_cast <const char *>(&it),sizeof(Pokemon));
        }
        File.close();
    }

    bool pokeAdd(const char *name, int id, const char *types) {
        Pokemon ans;
        checkName(ans,name);
        checkID(ans,id);
        checkType(ans,types);
        return (set.insert(ans)).second;
    }

    bool pokeDel(int id) {
        Pokemon tmp;
        checkID(tmp,id);
        return set.erase(tmp);
    }

    std::string pokeFind(int id) const {
        Pokemon tmp;
        checkID(tmp,id);
        auto it = set.find(tmp);
        if(it == set.end()) return "None";
        else return it->name;
    }

    std::string typeFind(const char *types) const {
        Pokemon tmp;
        checkType(tmp,types);
        std::vector <const Pokemon *> index;
        for(const auto &it : set)
            if((it.type | tmp.type) == it.type) index.push_back(&it);
        if(index.empty()) return "None";
        std::string ans = std::to_string(index.size());
        for(auto it : index)
            ans.append('\n' + std::string(it->name));
        return ans;
    }

    float attack(const char *type, int id) const {
        Pokemon tmp;
        checkID(tmp,id);
        checkType(tmp,type);
        auto it = set.find(tmp);
        if(it == set.end()) return -1; // Not found.
        int j = tmp.type._Find_first();// single type.
        float ans = 1;
        for(auto i = 0 ; i < 7 ; ++i) {
            if(it->type[i]) ans *= atkMap[j][i];
        }
        return ans;
    }

    int catchTry() const {
        if(set.empty()) return 0;
        Pokemon cur = *set.begin();
        int ans = 0;
        while(true) { // at most 8 times.
            int cnt = 0;
            for(auto it = ++set.begin() ; it != set.end() ; ++it) {
                if(judgeAtk(cur,*it)) {
                    ++cnt;
                    cur.type |= it->type; // Add existing type.
                }
            }
            if(ans == cnt) break;
            ans = cnt;
        }
        return ans + 1;
    }

    struct iterator {
        std::set <Pokemon>::iterator iter;
        std::set <Pokemon> *setptr;

        iterator() {
            setptr = nullptr;
        }

        iterator(const std::set <Pokemon>::iterator &tmp,
                 std::set <Pokemon> *ptr) {
            iter   = tmp;
            setptr = ptr;
        }

        iterator(const iterator &tmp) :iterator(tmp.iter,tmp.setptr) {}

        iterator &operator++() {
            if(!setptr || iter == setptr->end())
                throw IteratorException(
                    "Iterator Error: Invalid Iterator"
                ); 
            ++iter;
            return *this;
            //TO DO: ++迭代�?
        }

        iterator &operator--() {
            if(!setptr || iter == setptr->begin())
                throw IteratorException(
                    "Iterator Error: Invalid Iterator"
                ); 
            --iter;
            return *this;
            //TO DO: --迭代�?
        }
        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        iterator operator--(int) {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }
        iterator &operator =(const iterator &rhs) {
            iter = rhs.iter;
            setptr = rhs.setptr;
            return *this;
        }
        bool operator == (const iterator &rhs) const {
            return iter == rhs.iter;
        }
        bool operator != (const iterator &rhs) const {
            return iter != rhs.iter;
        }
        const Pokemon &operator*() const {
            if(!setptr || iter == setptr->end())
                throw IteratorException(
                    "Iterator Error: Dereference Error"
                );
            return *iter;
        }
        const Pokemon *operator->() const {
            if(!setptr || iter == setptr->end())
                throw IteratorException(
                    "Iterator Error: Dereference Error"
                );
            return &(*iter);            
        }
    };

    iterator begin() {
        return iterator(set.begin(),&set);
        //return: 返回指向图鉴头部的迭代器
    }

    iterator end() {
        return iterator(set.end(),&set);
    }
};

