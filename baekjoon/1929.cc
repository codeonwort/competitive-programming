// ID:  1929 (소수 구하기)
// URL: https://www.acmicpc.net/problem/1929
// Category: Sieve of Eratosthenes

#include <iostream>
#include <stdio.h>
#include <memory.h>
using namespace std;

const int MAX = 1000001;
bool isPrime[MAX];

int main() {
	int m, n;
	cin >> m >> n;
	
	memset(isPrime, 1, sizeof(isPrime));
	isPrime[1] = false;
	for(long long i=2; i<=n; i++){
		for(long long j=i*i; j<=n; j+=i){
			isPrime[j] = false;
		}
	}

	for(int i=m; i<=n; i++){
		if(isPrime[i]) printf("%d\n", i);
	}
}
