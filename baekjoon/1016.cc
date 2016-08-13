// ID:	1016 (제곱ㄴㄴ수)
// URL:	https://www.acmicpc.net/problem/1016

// Baekjoon online judge doesn't support Haskell currently

// all n = app (a: arbitrary, p: prime) are excluded
// reference: SquareFree section in http://www.topcoder.com/tc?module=Static&d1=match_editorials&d2=srm190

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef unsigned long long ll;

void fillPrimes(vector<ll>& primesSquared, ll m) {
	ll k = (ll)sqrt((double)m);
	vector<bool> isPrime(k+1);

	for(ll i=2; i<=k; i++) isPrime[i] = true;
	for(ll i=2; i<=k; i++){
		if(isPrime[i]){
			for(ll j=i*i; j<=k; j+=i) isPrime[j] = false;
			primesSquared.push_back(i*i);
		}
	}
}

ll recurse(vector<ll>& primesSquared, int i, ll soFar, ll m) {
	if(i == primesSquared.size() || primesSquared[i] * soFar > m) return 0;
	ll ret = (m / primesSquared[i]) / soFar;
	ret += recurse(primesSquared, i+1, soFar, m);
	ret -= recurse(primesSquared, i+1, primesSquared[i] * soFar, m);
	return ret;
}

ll squareFrees(vector<ll>& primesSquared, ll m) {
	return recurse(primesSquared, 0, 1, m);
}

int main() {
	ll min,max;
	vector<ll> primesSquared;

	cin >> min >> max;

	fillPrimes(primesSquared, max);

	ll numFree = squareFrees(primesSquared, max) - squareFrees(primesSquared, min-1);
	ll num = max - min + 1 - numFree;

	cout << num << endl;

	return 0;
}
