#include <iostream>
#include <deque>


signed main() {
    int n;
    std::cin >> n;
    std::deque <int> d;
    while(n--) {
        int x;
        std::cin >> x;
        switch(x) {
            case 1:
                std::cin >> x;
                d.push_front(x);
                break;
            case 2:
                std::cin >> x;
                d.push_back(x);
                break;
            case 3:
                d.pop_front();
                break;
            case 4:
                d.pop_back();
                break;
            case 5:
                std::cout << d.front() << '\n';
                break;
            case 6:
                std::cout << d.back() << '\n';
                break;
        }
    }
    return 0;
}