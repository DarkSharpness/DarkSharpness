#include<iostream>
#include<chrono>
#include<unordered_map>
#include<cstring>
using namespace std;

struct custom_hash {
	static uint64_t splitmix64(uint64_t x) {
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}
};

struct charptr_hash{
    static uint64_t splitmix64(uint64_t x) {
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(char * x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        uint64_t T=0;
        while(*x!=0)
            T=T*(100000000000000003)+(*x);
        return splitmix64(T + FIXED_RANDOM);
	}
};



unordered_map<uint64_t, string, custom_hash> safe_map;
custom_hash C;
int x;


int main()
{
    while(cin >> x)
        cout << C(x) << "\n";
    return 0;
}
