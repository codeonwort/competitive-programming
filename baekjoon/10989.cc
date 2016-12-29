// ID:  10989 (수 정렬하기 3)
// URL: https://www.acmicpc.net/problem/10989

#include <stdio.h>
using namespace std;

const int MAX = 10000;
int occur[MAX + 1];

void solve() {
	int n;
	scanf("%d", &n);

	for(int i=0; i<n; i++){
		int x;
		scanf("%d", &x);
		occur[x]++;
	}

	for(int i=1; i<=MAX; i++){
		for(int j=0; j<occur[i]; j++){
			printf("%d\n", i);
		}
	}
}

int main() {
	solve();
	return 0;
}
