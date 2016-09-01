// ID:  1932 (숫자삼각형)
// URL: https://www.acmicpc.net/problem/1932

#include <iostream>

using namespace std;

// dp[i][j]: maximum sum from (1,1) to (i,j)
int dp[500][500];
int matrix[500][500];

int main() {
	int n;

	// input
	cin >> n;
	for(int i=0; i<n; i++){
		for(int j=0; j<=i; j++){
			cin >> matrix[i][j];
			dp[i][j] = 0;
		}
	}

	// initial solution
	dp[0][0] = matrix[0][0];

	// DP
	for(int i=1; i<n; i++){
		dp[i][0] = matrix[i][0] + dp[i-1][0];
		for(int j=1; j<=i; j++){
			dp[i][j] = matrix[i][j] + max(dp[i-1][j], dp[i-1][j-1]);
		}
	}

	int soln = dp[n-1][0];
	for(int i=1; i<n; i++){
		if(dp[n-1][i] > soln) soln = dp[n-1][i];
	}
	cout << soln << endl;

	return 0;
}
