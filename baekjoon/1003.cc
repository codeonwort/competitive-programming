// ID:	1003 (피보나치 함수)
// URL:	https://www.acmicpc.net/problem/1003

#include <iostream>
#define LL long long

using namespace std;

void solve();

struct count {
	LL zero;
	LL one;
};

int main() {
	int t;
	cin >> t;
	while(t --> 0) solve();
	return 0;
}

void solve() {
	int n;
	count fib[40];

	// input
	cin >> n;

	// initial solution
	fib[0].zero = 1;
	fib[0].one = 0;
	fib[1].zero = 0;
	fib[1].one = 1;

	// DP
	for(int i=2; i<=n; i++){
		fib[i].zero = fib[i-1].zero + fib[i-2].zero;
		fib[i].one = fib[i-1].one + fib[i-2].one;
	}

	cout << fib[n].zero << ' ' << fib[n].one << endl;
}
