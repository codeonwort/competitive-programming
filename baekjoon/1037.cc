// ID:  1037 (약수)
// URL: https://www.acmicpc.net/problem/1037

// This is 'absurd' logic.
// Just multiply the smallest and the largest proper divisors
// and you get the answer... (see their factorization forms)

#include <memory.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
const ll MAX = 1e6 + 1;
bool isPrime[MAX];
int factors[MAX];

void getPrimes() {
	memset(isPrime, true, sizeof(isPrime));
	isPrime[0] = false; isPrime[1] = false;
	for(ll i=2; i<MAX; i++){
		if(isPrime[i]){
			for(ll j=i*i; j<MAX; j+=i){
				isPrime[j] = false;
			}
		}
	}
}

int main() {
	// input
	int n;
	scanf("%d", &n);
	vector<int> divisors(n);
	for(int i=0; i<n; i++) scanf("%d", &divisors[i]);

	// find primes
	getPrimes();

	vector<int> primes;
	for(int i=2; i<MAX; i++){
		if(isPrime[i]) primes.push_back(i);
	}

	// factorize each divisor
	memset(factors, 0, sizeof(factors));
	for(int i=0; i<n; i++){
		// v = factorization of d
		vector<int> v;
		int d = divisors[i];
		for(int j=0; j<primes.size();){
			if(d % primes[j] == 0){
				v.push_back(primes[j]);
				d /= primes[j];
			}else{
				j++;
			}
		}
		v.push_back(0);
		int p = v[0], cnt = 1;
		for(int j=1; j<v.size(); j++){
			if(v[j] != v[j-1]){
				factors[v[j-1]] = max(factors[v[j-1]], cnt);
				cnt = 1;
				p = v[j];
			}else{
				cnt++;
			}
		}
	}

	// calculate the answer
	ll answer = 1;
	vector<pair<ll,ll>> temp;
	for(int i=1; i<MAX; i++){
		if(factors[i] > 0){
			temp.push_back(pair<int,int>(i, factors[i]));
		}
	}
	if(temp.size() == 1) answer = pow(temp[0].first, temp[0].second + 1);
	else{
		for(int i=0; i<temp.size(); i++){
			answer *= pow(temp[i].first, temp[i].second);
		}
	}

	// output
	printf("%lld\n", answer);

	return 0;
}
