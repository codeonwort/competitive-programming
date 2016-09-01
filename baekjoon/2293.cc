// ID:  2293 (동전 1)
// URL: https://www.acmicpc.net/problem/2293

#include <iostream>

using namespace std;

int main() {
	int n; // number of types of coins
	int k; // goal
	int coins[101]; // value of each type of coin
	int dp[10001]; // dp[i]: combinations that sum up to i

	// input
	cin >> n >> k;
	for(int i=0; i<n; i++) cin >> coins[i];

	// initial solution: only one way to make 0
	dp[0] = 1;
	for(int i=1; i<=k; i++) dp[i] = 0;

	// DP
	for(int j=0; j<n; j++){
		int coin = coins[j];
		for(int i=0; i<=k; i++){
			if(i >= coin) dp[i] += dp[i-coin];
		}
	}

	// debug
	//for(int i=0; i<=k; i++) cout << dp[i] << ' ';
	//cout << endl;

	int soln = dp[k];
	cout << soln << endl;

	return 0;
}
