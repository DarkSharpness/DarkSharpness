#include <bits/stdc++.h>
const int N = 4096 / 4;
const int M = 1e8 / N;
/**
 * Get specified 4096 * n bytes from the memory.
 * @param n
 * @return the address of the block
 */
int* getNewBlock(int n);

/**
 * Free specified 4096 * n bytes from the memory.
 * @param block the pointer to the block
 * @param n
 */
void freeBlock(const int* block, int n);

// include whatever you want

class Allocator {
public:
    struct node {
        int cnt;
        int siz;
    };
    struct block {

    };
    std::unordered_map <int *,int *> mp;
    std::unordered_map <int *,node> cnt;
    std::vector <int *> avail[N];
    std::vector <int *> dark[M];
    Allocator() {
        // TODO£º constructor ¹¹Ôìº¯Êý
        
    }

    ~Allocator() {
        for(auto it : cnt) {
            freeBlock(it.first,it.second.siz);
        }
        for(int i = 1 ; i < M ; ++i) {
            for(auto it : dark[i]) {
                freeBlock(it,i);
            }
        }
    }


    /**
     * Allocate a sequence of memory space of n int.
     * @param n
     * @return the pointer to the allocated memory space
     */
    int* allocate(int n) {
        if(!n) return nullptr;
        if(n < N) {
            for(int j = n ; j < N ; ++j) {
                if(avail[j].empty()) continue;

                int *ptr = avail[j].back();
                avail[j].pop_back();

                int *src = mp[ptr];
                const int ret = j - n;

                if(ret) {
                    avail[ret].push_back(ptr + n);
                    mp[ptr + n] = src;
                    ++cnt[src].cnt;
                }


                return ptr;
            }
        }


        const int num = (n - 1)/ N + 1;
        const int ret = num * N - n;
        const int del = N - ret;

        int *ptr;
        if(dark[num].empty()) {
            ptr = getNewBlock(num);
        } else {
            ptr = dark[num].back();
            dark[num].pop_back();
        }


        mp[ptr] = ptr;
        if(ret == 0) {
            cnt[ptr] = (node){1,num};
            return ptr;
        }
        else {
            avail[ret].push_back(ptr + n);
            mp[ptr + n] = ptr;
            cnt[ptr] = (node){2,num};
            return ptr;
        }
    }

    /**
     * Deallocate the memory that is allocated by the allocate member
     * function. If n is not the number that is called when allocating,
     * the behaviour is undefined.
     */
    void deallocate(int* pointer, int n) {
        auto iter  = mp.find(pointer);
        auto iter2 = cnt.find(iter->second);
        mp.erase(iter);

        if(--iter2->second.cnt == 0) {
            dark[iter2->second.siz].push_back(iter2->first);
            cnt.erase(iter2);
        }


        // TODO£º deallocate the pointer
    }

private:
    // Add whatever you want to add
};