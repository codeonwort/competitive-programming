// ID:  9465 (스티커)
// URL: https://www.acmicpc.net/problem/9465

/* lessons learned
Time limit  : 3s
Accepted in : 2.92s (long long -> int)
Accepted in : 1.27s (cin/cout -> scanf/printf)
 */

#include <stdio.h>

// dp[i][j]: maximum score from column 0 to i
//           j == 0 : in i-th column, upper sticker is selected
//           j == 1 : in i-th column, lower sticker is selected
//           j == 2 : in i-th column, nothing is selected
int dp[100000][3];

int scores[100000][2];

void solve();

int max(int a, int b) { return a>b ? a : b; }

int main() {
	int t;
	scanf("%d", &t);
	while(t --> 0) solve();
	return 0;
}

void solve() {
	int n, i, soln;

	// input
	scanf("%d", &n);
	for(i=0; i<n; i++) scanf("%d", &scores[i][0]);
	for(i=0; i<n; i++) scanf("%d", &scores[i][1]);
	
	// initial solution
	dp[0][0] = scores[0][0];
	dp[0][1] = scores[0][1];
	dp[0][2] = 0;
	dp[1][0] = scores[1][0] + scores[0][1];
	dp[1][1] = scores[1][1] + scores[0][0];
	dp[1][2] = max(scores[0][0], scores[0][1]);
	
	// DP
	for(i=2; i<n; i++){
		dp[i][0] = scores[i][0] + max(dp[i-1][2], dp[i-1][1]);
		dp[i][1] = scores[i][1] + max(dp[i-1][2], dp[i-1][0]);
		dp[i][2] = max(dp[i-1][0], max(dp[i-1][1], dp[i-1][2]));
	}

	soln = max(dp[n-1][0], max(dp[n-1][1], dp[n-1][2]));
	printf("%d\n", soln);
}
