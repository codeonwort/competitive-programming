// ID:  716A (Crazy Computer)
// URL: http://codeforces.com/problemset/problem/716/A

#include <iostream>
using namespace std;

const unsigned int MAX = 1e5 + 1;
unsigned int times[MAX];

int main() {
	unsigned int n, delay;

	cin >> n >> delay;
	for(int i=0; i<n; i++){
		cin >> times[i];
	}

	int cnt = 1;
	for(int i=1; i<n; i++){
		if(times[i] - times[i-1] > delay) cnt = 0;
		cnt++;
	}

	cout << cnt << endl;

	return 0;
}
