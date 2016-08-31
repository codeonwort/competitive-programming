#include <iostream>
#include <cmath>

#define LL long long

using namespace std;

// ID:	10253 (헨리)
// URL:	https://www.acmicpc.net/problem/10253

void solve();

int main() {
	int t;

	cin >> t;

	while(t --> 0) solve();

	return 0;
}

LL gcd(LL a, LL b) {
	if(b == 0) return a;
	return gcd(b, a%b);
}

void solve() {
	LL a, b;

	cin >> a >> b;

	int cnt = 0;
	while(a != 1 && cnt++ < 10){
		LL x = ceil(b/a) + 1;
		// a/b - 1/x = ax/bx - b/bx = (ax-b)/bx
		LL a1 = a*x - b;
		LL b1 = b * x;
		LL common = gcd(a1, b1);
		a = a1 / common;
		b = b1 / common;
	}

	cout << b << endl;
}
