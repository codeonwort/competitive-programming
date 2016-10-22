// ID:  9520 (PUTNIK)
// URL: https://www.acmicpc.net/problem/9520

#include <stdio.h>
#include <algorithm>
using namespace std;

// dp[i][j]: min. cost to visit city 1 ~ max(i,j)
int dp[1501][1501];
int cost[1501][1501];
const int INF = 987654321;

int main() {
	int n;

	// input
	scanf("%d", &n);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			scanf("%d", &cost[i][j]);
			dp[i][j] = INF;
		}
	}

	// DP: base case
	dp[1][2] = dp[2][1] = cost[2][1];

	// DP: recursive case
	for(int i=1; i<n; i++){
		for(int j=1; j<n; j++){
			if(i == j) continue;
			dp[max(i,j)+1][j] = min(dp[max(i,j)+1][j], cost[max(i,j)+1][i] + dp[i][j]);
			dp[i][max(i,j)+1] = min(dp[i][max(i,j)+1], dp[i][j] + cost[j][max(i,j)+1]);
		}
	}

	// output
	int soln = INF;
	for(int i=1; i<=n; i++){
		soln = min(soln, min(dp[n][i], dp[i][n]));
	}
	printf("%d\n", soln);

	return 0;
}
