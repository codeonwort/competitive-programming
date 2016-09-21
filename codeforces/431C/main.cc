// ID:  431C (k-Tree)
// URL: http://codeforces.com/problemset/problem/431/C

#include <iostream>
using namespace std;

#define LL long long
const int MOD = 1e9 + 7;

// dp[i][j][0]: from root to depth i, number of paths whose cost is j,
//              and no edge has a weight equal or greater than d
// dp[i][j][1]: from root to depth i, number of paths whose cost is j,
//              and at least one edge has a weight equal or greater than d
// answer is the sum dp[1][n][1] + ... + dp[n][n][1]
LL dp[101][101][2];
LL subsum0[101], subsum1[101];
LL sum(LL subsum[], int left, int right) {
	if(right < 0 || left > right) return 0;
	return subsum[right] - (left-1 >= 0 ? subsum[left-1] : 0);
}

int main() {
	// n: total weight of path
	// k: k-Tree
	// d: constraint
	int n, k, d;

	// input
	cin >> n >> k >> d;

	// DP: base case
	for(int i=0; i<=100; i++){
		for(int j=0; j<=100; j++){
			dp[i][j][0] = dp[i][j][1] = 0;
		}
	}
	dp[0][0][0] = 1;
	dp[0][0][1] = 0;

	// DP: recursive case
	for(int i=1; i<=n; i++){
		subsum0[0] = dp[i-1][0][0];
		subsum1[0] = dp[i-1][0][1];
		for(int j=1; j<=n; j++){
			subsum0[j] = subsum0[j-1] + dp[i-1][j][0];
			subsum1[j] = subsum1[j-1] + dp[i-1][j][1];
		}
		for(int j=1; j<=n; j++){
			dp[i][j][0] = sum(subsum0, j-d+1, j-1) % MOD;
			dp[i][j][1] = sum(subsum1, j-k, j-1) % MOD + sum(subsum0, j-k, j-d) % MOD;
		}
	}

	LL soln = 0;
	for(int i=1; i<=n; i++){
		soln = (soln + dp[i][n][1]) % MOD;
	}
	cout << soln << endl;

	return 0;
}
