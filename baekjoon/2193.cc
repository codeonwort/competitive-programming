// ID:  2193 (이친수)
// URL: https://www.acmicpc.net/problem/2193

#include <iostream>
#define LL long long

using namespace std;

int main() {
	int n;

	// input
	cin >> n;

	// dp[i][j]: count of i bits pinary numbers
	//           where i-th bit is j
	LL dp[90][2];

	// initial solution
	dp[0][0] = 0;
	dp[0][1] = 1;

	// DP
	for(int i=1; i<n; i++){
		dp[i][0] = dp[i-1][0] + dp[i-1][1];
		dp[i][1] = dp[i-1][0];
	}

	LL soln = dp[n-1][0] + dp[n-1][1];
	cout << soln << endl;

	return 0;
}
