// ID:  13458 (시험 감독)
// URL: https://www.acmicpc.net/problem/13458

#include <stdio.h>

int A[1000000];

int main() {
	int n, B, C;
	scanf("%d", &n);
	for(int i=0; i<n; i++) scanf("%d", A + i);
	scanf("%d %d", &B, &C);

	long long answer = 0;
	for(int i=0; i<n; i++){
		answer += 1;
		A[i] -= B;
		if(A[i] > 0){
			answer += A[i] / C + (A[i] % C == 0 ? 0 : 1);
		}
	}
	printf("%lld\n", answer);
}
