// ID:	3046 (R2)
// URL:	https://www.acmicpc.net/problem/3046

// Baekjoon online judge doesn't support Haskell currently

#include <stdio.h>

int solve(int r1, int s) {
	return 2*s - r1;
}

int main() {
	int r1, s;

	scanf("%d%d", &r1, &s);
	printf("%d", solve(r1, s));

	return 0;
}
