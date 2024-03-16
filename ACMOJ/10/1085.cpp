#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

const int __N = 100;
using key_t = int;

class FHQTreap {
  private:
    size_t seed;
    size_t random() { return seed *= 181919415411LL; }
    struct node {
        key_t  key;
        size_t weight; /* Random Weight */
        size_t siz;    /* Siz */
        size_t cnt;
        node * l;
        node * r;
    };
    size_t tot; // Count of nodes.
    node t[__N];

    /* Update size. */
    void update_size(node *cur) {
        cur->siz = cur->cnt + cur->l->siz + cur->r->siz;
    }

    /* Create a new node. */
    size_t create_node(key_t key) {
        t[++tot] = (node) {key,random(),1,1,t,t};
        return tot;
    }

    void split_key(size_t id,key_t key,size_t &l,size_t &r) {
        if(!id) return (void) (l = r = 0);
        if(t[id].key <= key) {
            l = id;
            split_key(t[l].)
        }

    }

    void split_rank() {

    }

  public:
    FHQTreap() { /* Anti-hack initialization. */
        int *tmp = new int;
        seed = reinterpret_cast <size_t> (tmp);
        delete tmp;
    }

};

signed main() {


    return 0;
}