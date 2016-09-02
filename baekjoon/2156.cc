// ID:  2156 (포도주 시식)
// URL: https://www.acmicpc.net/problem/2156

#include <iostream>
#include <algorithm>

/* lessons learned
If you set DP table as follows:

dp[i][j]: maximum score for wine 1 ~ wine i
          where wine (i-j-1) is the previous take

It ommits the cases in which two successive wines are not took
For example, it doesn't consider 123456 -> 12xx56 (middle wines are not took)

Results in wrong answer!
*/

using namespace std;

int main() {
	int n;
	int scores[10001];

	// input
	cin >> n;
	for(int i=1; i<=n; i++) cin >> scores[i];

	// dp[i][j]: maximum score for wine 1 ~ wine i
	//           where wine i is j-th of consecutive takes
	//           (j == 0 means don't take wine i)
	int dp[10001][3];
	for(int i=0; i<=n; i++){
		dp[i][0] = dp[i][1] = 0;
	}

	// initial solution
	dp[1][1] = scores[1];
	
	// DP
	for(int i=2; i<=n; i++){
		dp[i][0] = max(dp[i-1][0], max(dp[i-1][1], dp[i-1][2]));
		dp[i][1] = scores[i] + dp[i-1][0];
		dp[i][2] = scores[i] + dp[i-1][1];
	}

	// output
	int soln = max(dp[n][0], max(dp[n][1], dp[n][2]));
	cout << soln << endl;

	return 0;
}
