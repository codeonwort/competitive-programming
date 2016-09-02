// ID:  9465 (스티커)
// URL: https://www.acmicpc.net/problem/9465

/* lessons learned
Time limit  : 3s
Accepted in : 2.92s

What? Why so tight?

long long is too slow. got TLE
- answer can be represented as int
- changed the types of dp[][] and scores[][]
  from long long to int
- scanf is super faster than cin.
  - it reduces accepted time from 2.92s to 1.72s.
  - see '9465.c' for scanf version.
 */

#include <iostream>
#include <algorithm>

using namespace std;

// dp[i][j]: maximum score from column 0 to i
//           j == 0 : in i-th column, upper sticker is selected
//           j == 1 : in i-th column, lower sticker is selected
//           j == 2 : in i-th column, nothing is selected
int dp[100000][3];

int scores[100000][2];

void solve();

int main() {
	int t;
	cin >> t;
	while(t --> 0) solve();
	return 0;
}

void solve() {
	int n;

	// input
	cin >> n;
	for(int i=0; i<n; i++) cin >> scores[i][0];
	for(int i=0; i<n; i++) cin >> scores[i][1];
	
	// initial solution
	dp[0][0] = scores[0][0];
	dp[0][1] = scores[0][1];
	dp[0][2] = 0;
	dp[1][0] = scores[1][0] + scores[0][1];
	dp[1][1] = scores[1][1] + scores[0][0];
	dp[1][2] = max(scores[0][0], scores[0][1]);
	
	// DP
	for(int i=2; i<n; i++){
		dp[i][0] = scores[i][0] + max(dp[i-1][2], dp[i-1][1]);
		dp[i][1] = scores[i][1] + max(dp[i-1][2], dp[i-1][0]);
		dp[i][2] = max(dp[i-1][0], max(dp[i-1][1], dp[i-1][2]));
	}

	int soln = max(dp[n-1][0], max(dp[n-1][1], dp[n-1][2]));
	cout << soln << endl;
}
