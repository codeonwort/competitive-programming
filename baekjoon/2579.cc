// ID:  2579 (계단 오르기)
// URL: https://www.acmicpc.net/problem/2579

#include <iostream>
#define LL long long

using namespace std;

int main() {
	int n;
	LL score[301];

	// input
	cin >> n;
	for(int i=1; i<=n; i++){
		cin >> score[i];
	}

	// dp[i][j]: maximum score at i-th stair (i starts from 1)
	//           where j is the previous stair
	LL dp[301][301];
	for(int i=0; i<=n; i++){
		for(int j=0; j<=n; j++){
			dp[i][j] = 0;
		}
	}

	// initial solution
	dp[1][0] = score[1];
	if(n > 1){
		dp[2][0] = score[2];
		dp[2][1] = score[1] + score[2];
	}

	// DP
	for(int i=3; i<=n; i++){
		dp[i][i-1] = score[i] + dp[i-1][i-3];
		if(i > 3) dp[i][i-2] = score[i] + max(dp[i-2][i-3], dp[i-2][i-4]);
		else dp[i][i-2] = score[i] + dp[i-2][i-3];
	}

	LL soln = max(dp[n][n-1], dp[n][n-2]);
	cout << soln << endl;

	return 0;
}
