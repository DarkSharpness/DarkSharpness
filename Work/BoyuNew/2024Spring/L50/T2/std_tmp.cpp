#include <iostream>
#include <queue>
using namespace std;

signed main() {
	int n;
	priority_queue <long long,
        vector <long long>,
        greater <long long>> q;

	cin >> n;

	for (int i = 0 ; i < n ; ++i) {
		int x;
		cin >> x;
		q.push(x);
    }

    for (int i = 1 ; i < n ; ++i) {
		long long z = q.top();
      	q.pop();
      	z += q.top();
      	q.pop();
        cout << z << ' ';
      	q.push(z);
    }
    return 0;
}
