// ID:  2292 (벌집)
// URL: https://www.acmicpc.net/problem/2292

#include <iostream>
using namespace std;

void solve() {
	long long n;
	cin >> n;

	long long x = 1;
	while(true){
		long long int y = 3*x*(x-1) + 1;
		if(y >= n) break;
		x++;
	}
	cout << x << endl;
}

int main() {
	solve();
	return 0;
}
