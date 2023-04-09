#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <string>
#include <fstream>

constexpr size_t kFile_Length = 31;

class file_manager : public std::fstream {
  private:
    char c[kFile_Length];

  public:
    file_manager() = delete;
    file_manager(const char *__c) noexcept { strcpy(c,__c); }
    ~file_manager() = default;

    void open(std::ios_base::openmode _mode = (std::ios_base::openmode)28) 
    { this->std::fstream::open(c,_mode); }

    /**
     * @brief Try creating a new file and open it.
     * 
     * @return True if success || False if file existed. 
     */
    bool create() {
        open();
        if(good()) return false;
        close(); open(std::ios::out);
        close(); open();
        return true;
    }

    /* Read to an object with given size. */
    template <class T>
    void read_object(T &r,size_t __n = sizeof(T)) 
    { std::fstream::read((char *)&r,__n); }

    /* Write to an object with given size. */
    template <class T>
    void write_object(const T &r,size_t __n = sizeof(T)) 
    { std::fstream::write((const char *)&r,__n); }

};

namespace b_plus {

const int N = 100;
using key_t = char[32];
using T     = size_t;

class tree {
  private:
    using diff_t = std::ptrdiff_t;

    struct value_t {
        key_t key;
        union { T value; diff_t index; };
    };

    struct node {
        value_t data[N];
        diff_t  next; /* Pointer to next data. */
    };

  private:
    file_manager file; /* Main data. */
    file_manager bin ; /* Rubbish bin. */

  public:

    tree(const char *__a,const char *__b)
    noexcept : file(__a) , bin(__b) {
        if(file.create()) {}
        if(bin .create()) { bin.write_object(diff_t(0)); }
    }

    tree() = delete;
    tree(tree &&)      = delete;
    tree(const tree &) = delete;
    tree &operator = (tree &&)      = delete;
    tree &operator = (const tree &) = delete;
    ~tree() { file.close(); bin.close(); }

    void work() {
        node tmp;


    }

  public:

};

}


signed main() {

    return 0;
}
