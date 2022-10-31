#include "ICPC.h"
namespace ICPC {
    

// Mapping a char into number
int charMap[128];
// Maximum characters as key.
int dfn;

class Trie {
    private:
    struct node {
        int nxt[63]; // The index of next node
        int rank;
        node () {
            rank = -1;
            memset(nxt,-1,sizeof(nxt));
        }
    };
    std::vector <node> nodeData;
    public:
    /// @brief Insert a string
    inline void insert(const string &str,int _rank) {
        int root  = 0;
        int len   = 0;
        int next  = 0;
        while(str[len] != '\0') {
            next = nodeData[root].nxt[charMap[(int)str[len]]];
            if(next == -1) {
                next = nodeData[root].nxt[charMap[(int)str[len]]] 
                     = nodeData.size();
                nodeData.emplace_back();
            }
            root = next;
            ++len;
        }
        nodeData[root].rank = _rank;
    }
    /// @brief Find the ID of a string
    inline int find(const string &str) {
        int root  =  0;
        int len   =  0;
        int next  = -1;
        while(str[len] != '\0') {
            next = nodeData[root].nxt[charMap[(int)str[len]]];
            if(next == -1) return -1;
            root = next;
            ++len;
        }
        // Not found
        if(next == 0) return -1;
        else return nodeData[root].rank;
    }
    Trie() {
        nodeData.resize(1);
    }
}nameTrie;


void prework() {
    for(int i = 'a' ; i <= 'z' ; ++i) {
        charMap[i] = ++dfn;
    }
    for(int i = 'A' ; i <= 'Z' ; ++i) {
        charMap[i] = ++dfn;
    }
    for(int i = '0' ; i <= '9' ; ++i) {
        charMap[i] = ++dfn;
    }
    charMap['_'] = ++dfn;
}
}
using namespace ICPC;

int main() {
    prework();
    read >> buffer;
    nameTrie.insert(buffer,10);
    read >> buffer;
    write << "ID: ";
    write << nameTrie.find(buffer);
}

