// ID:	1110 (더하기 사이클)
// URL:	https://www.acmicpc.net/problem/1110

// Baekjoon online judge doesn't support Haskell currently

#include <stdio.h>

int solve(int n) {
	int m,i,p,q;

	i = 0;
	m = n;

	do {
		p = m / 10;
		q = m % 10;
		m = 10*q + ((p+q)%10);
		i++;
	} while (m != n);

	return i;
}

int main() {
	int n;

	scanf("%d", &n);
	printf("%d", solve(n));
}
