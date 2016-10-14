// ID:  11401 (이항 계수 3)
// URL: https://www.acmicpc.net/problem/11401
// Category: Numer Theory, Fermat's Theorem

#include <iostream>
using namespace std;

typedef unsigned long long LL;
const LL MOD = 1e9 + 7;

LL power(LL a, LL x) {
	if(x == 1) return a;
	if(x & 1) return (a * power((a*a) % MOD, x/2)) % MOD;
	return power((a*a) % MOD, x/2) % MOD;
}
LL inverse(LL a) { return power(a, MOD-2); }

LL mult(LL a, LL b) { return (a * b) % MOD; }

LL fact(LL n) {
	int ret = 1;
	while(n > 1){
		ret = (ret * n) % MOD;
		n--;
	}
	return ret;
}

LL C(LL n, LL k) {
	return mult(mult(fact(n), inverse(fact(k))), inverse(fact(n-k)));
}

int main() {
	LL n,k;
	cin >> n >> k;
	cout << C(n, k) << endl;
	return 0;
}
