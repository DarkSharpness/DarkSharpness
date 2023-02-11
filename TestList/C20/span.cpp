#include <span>
#include <array>
#include <vector>
#include <iostream>
using namespace std;

int main() {
    int a[] = {0,1,2};

    span <int> s(a);
    array <int,10> tmp {1,2,3,4,5};
    span <int> sa(tmp);

    vector <int> vec{2,3,4};
    span <int> aa(vec.begin(),vec.end()); // from begin to end
    span <int,3> g(vec.begin(),vec.end());// second param useless
    span <const int,5> t(vec.cbegin()+2,vec.cbegin());
    for(auto iter : t) {
        cout << iter << endl;
    }
    return 0;
}