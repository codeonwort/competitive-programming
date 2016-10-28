// ID:  11049 (행렬 곱셈 순서)
// URL: https://www.acmicpc.net/problem/11049

#include <stdio.h>
#include <algorithm>
using namespace std;

const long long INF = 1e16;
const int MAX = 500;
int rows[MAX], cols[MAX];

// dp[i][j] = number of ways to multiply mat i ~ mat j
long long dp[MAX][MAX];

int main() {
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++) scanf("%d %d", rows + i, cols + i);

	for(int i=0; i<n; i++) dp[i][i] = 0;
	for(int a=1; a<n; a++){
		for(int i=0; i<n; i++){
			int j = i + a; if(j >= n) break;
			dp[i][j] = INF;
			for(int k=i; k<j; k++){
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + rows[i]*cols[k]*cols[j]);
			}
		}
	}

	printf("%lld", dp[0][n-1]);

	return 0;
}
