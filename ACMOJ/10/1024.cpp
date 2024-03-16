#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long
class MemoryPoolManager
{
private:
    char *head;
    /*
        head: the position of the first free block
    */
    size_t block_size, block_cnt;
    /*
        block_size: the size of each block (in bytes, at least 8);
        block_cnt: the maximum number of blocks
    */
public:
    MemoryPoolManager(char *ptr, size_t block_size_, size_t block_cnt_) : head(ptr), block_size(block_size_), block_cnt(block_cnt_)
    {
        //to do: code whatever you want here to initialize
        memset(ptr,0,block_cnt*block_size);// byte offset encoding
    }

    void *allocate()
    {
        //to do: return a pointer pointing at a free block (nullptr if no free block left)
        if(!block_cnt) return nullptr;
        --block_cnt;
        void *tmp = head;
        head += block_size + *reinterpret_cast <size_t*>(head);
        return tmp;
    }

    void free(void *ptr)
    {
        //to do: make a block ready for reuse (we will guarantee that ptr is a block acquired by previous allocation)
        if(ptr == nullptr) return;
        ++block_cnt;
        *reinterpret_cast<size_t*>(ptr) =
        (reinterpret_cast<char *>(head) -
         reinterpret_cast<char *>(ptr)) - block_size;
        head = reinterpret_cast<char *>(ptr);
    }
};


signed main() {

    return 0;
}