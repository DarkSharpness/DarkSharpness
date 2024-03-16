#include <iostream> // FUCK you Disk limit exceed
#include <cstdio>
using namespace std;

namespace LIST {
    struct NODE {
        NODE *next;
        int val;
    };
    NODE *head = nullptr;
    int len = 0;
    void init() { head = new NODE {nullptr,0}; ios::sync_with_stdio(false); }
    void insert(int i, int x) {
        ++i;++len;
        NODE *__p = head;
        while(--i) __p = __p->next; /* i = 1 : no move case */
        __p->next = new NODE {__p->next,x};
    }
    void remove(int i) {
        ++i;--len;
        NODE *__p = head;
        while(--i) __p = __p->next;
        NODE *__t = __p->next;
        __p = __p->next = __t->next;  
        delete __t;
    }
    void remove_insert(int i) {
        if(++i == len) return;
        NODE *__p = head;
        while(--i) __p = __p->next;
        NODE *__t = __p->next;
        __p = __p->next = __t->next;  
        while(__p->next) __p = __p->next;
        __p->next = __t;
        __t->next = nullptr;
    }
    void get_length() { cout << len << '\n'; }
    void query(int i) {
        if(++i > len) return (void)(cout << "-1\n");
        NODE *__p = head;
        while(i--) __p = __p->next;
        cout << __p->val << '\n';
    }
    void get_max() {
        if(!len) return (void)(cout << "-1\n");
        NODE *__p = head->next;
        int ans = __p->val;
        while(__p->next) {
            __p = __p->next;
            if(__p->val > ans) ans = __p->val;
        }
        cout << ans << '\n';
    }
    void clear() {
        while(head) {
            NODE *next = head->next;
            delete head;
            head = next;
        }
    }
}
int n;
int main() {
    cin >> n;
    int op, x, p;
    LIST::init();
    for (int _ = 0; _ < n; ++_)
    {
        cin >> op;
        switch(op) {
            case 0:
                LIST::get_length();
                break;
            case 1:
                cin >> p >> x;
                LIST::insert(p,x);
                break;
            case 2:
                cin >> p;
                LIST::query(p);
                break;
            case 3:
                cin >> p;
                LIST::remove(p);
                break;
            case 4:
                cin >> p;
                LIST::remove_insert(p);
                break;
            case 5:
                LIST::get_max();
                break;
        }
    }
    LIST::clear();
    return 0;
}