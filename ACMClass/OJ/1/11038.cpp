#include <iostream>

struct node {
    node* next;
    int index;
};

int main() {
    int m;
    std::ios::sync_with_stdio(false);
    std::cin >> m;
    node *head = new node {nullptr,1};
    node *cur  = head;
    for (int i = 2; i <= m; ++i) { cur = cur->next = new node {nullptr,i}; }
    cur->next  = head;
    int cnt = m;
    for (int i = 0; i < m - 1; ++i) {
        int x;
        std::cin >> x;
        x = (x - 1) % cnt;
        while(x--) cur = cur->next;
        cur->next = cur->next->next;
        --cnt;
    }
    std::cout << cur->index;
    return 0;
}
