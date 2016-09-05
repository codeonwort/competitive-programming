// ID:  11048 (이동하기)
// URL: https://www.acmicpc.net/problem/11048

#include <algorithm>
#include <iostream>
using namespace std;

int dp[1000][1000];

int main() {
	int n,m;
	int candies[1000][1000];

	// input
	cin >> n >> m;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			cin >> candies[i][j];
		}
	}

	// initial solution
	dp[0][0] = candies[0][0];
	for(int i=1; i<n; i++) dp[i][0] = dp[i-1][0] + candies[i][0];
	for(int i=1; i<m; i++) dp[0][i] = dp[0][i-1] + candies[0][i];

	// DP
	for(int i=1; i<n; i++){
		for(int j=1; j<m; j++){
			dp[i][j] = max(dp[i-1][j-1], dp[i-1][j]);
			dp[i][j] = max(dp[i][j], dp[i][j-1]);
			dp[i][j] += candies[i][j];
		}
	}

	// output
	int soln = dp[n-1][m-1];
	cout << soln << endl;

	return 0;
}
