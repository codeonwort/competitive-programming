// ID:  9520 (PUTNIK)
// URL: https://www.acmicpc.net/problem/9520

#include <stdio.h>
#include <algorithm>
using namespace std;

// dp[i][j]: min. cost to visit city 1 ~ i (i:start, j:end, i > j)
// dp2[i][j]: min. cost to visit city 1 ~ i (i:end, j:start, i > j)
int dp[1501][1501], dp2[1501][1501];
int cost[1501][1501];
const int INF = 987654321;

int main() {
	int n;

	// input
	scanf("%d", &n);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			scanf("%d", &cost[i][j]);
			dp[i][j] = dp2[i][j] = INF;
		}
	}

	// DP: base case
	dp[2][1] = dp2[2][2] = cost[2][1];
	dp[2][2] = dp2[2][1] = cost[1][2];

	// DP: recursive case
	for(int i=2; i<n; i++){
		for(int j=1; j<i; j++){
			dp[i+1][j] = min(dp[i+1][j], dp[i][j] + cost[i+1][i]);
			dp2[i+1][i] = min(dp2[i+1][i], dp[i][j] + cost[j][i+1]);

			dp2[i+1][j] = min(dp2[i+1][j], dp2[i][j] + cost[i][i+1]);
			dp[i+1][i] = min(dp[i+1][i], dp2[i][j] + cost[i+1][j]);
		}
	}

	// output
	int soln = min(dp[n][1], dp2[n][1]);
	for(int i=2; i<=n; i++){
		soln = min(soln, min(dp[n][i], dp2[n][i]));
	}
	printf("%d\n", soln);

	return 0;
}
