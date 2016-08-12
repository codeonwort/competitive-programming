// ID:	1978 (소수 찾기)
// URL:	https://www.acmicpc.net/problem/1978

// Baekjoon online judge doesn't support Haskell currently

#include <stdio.h>
#include <math.h>

int isPrime(int n) {
	int i;
	int sq = (int)sqrt((double)n);

	if(n <= 1) return 0;
	for(i=2; i<=sq; i++){
		if(n % i == 0) return 0;
	}
	return 1;
}

int main() {
	int n, i, ary[100];
	int c = 0;

	scanf("%d", &n);
	for(i=0; i<n; i++){
		scanf("%d", ary + i);
		if(isPrime(ary[i])) c++;
	}

	printf("%d", c);

	return 0;
}
