// ID:	2355 (시그마)
// URL:	https://www.acmicpc.net/problem/2355

// Baekjoon online judge doesn't support Haskell currently

#include <stdio.h>

typedef long long ll;

int main() {
	ll i,j,k;
	ll sum_to_i_1, sum_to_j;

	scanf("%lld %lld", &i, &j);

	if(j < i){
		// force that i <= j
		k = i; i = j; j = k;
	}

	sum_to_i_1 = i & 1 ? (i-1)/2 * i : (i-1)*(i/2);
	sum_to_j = j & 1 ? j * ((j+1) / 2) : (j/2) * (j+1);

	printf("%lld", sum_to_j - sum_to_i_1);

	return 0;
}
