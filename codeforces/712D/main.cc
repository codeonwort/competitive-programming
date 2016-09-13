// ID:  712D (Memory and Scores)
// URL: http://codeforces.com/problemset/problem/712/D

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXGAP = 400000 + 200;
const int i0 = 200000 + 100;
const int MOD = 1e9 + 7;

// dp[i][j]: on i-th trial, the number of games where
//           (memory's score - lexa's score) is (j - 200000)
//           maximum score gap is -200099 and 200099
long long int dp[100][MAXGAP + 1];
long long int psum[MAXGAP + 1]; // partial sum of dp[i-1]

long long int partialSum(int start, int end, int left, int right) {
	//return psum[min(right, end)] - (start > left ? psum[start-1] : 0);
	return psum[min(MAXGAP, end)] - (start > 0 ? psum[start-1] : 0);
}

int main() {
	int a, b, k, t;

	// input
	cin >> a >> b >> k >> t;

	// init
	for(int i = 0; i < 100; i++){
		for(int j = 0; j <= MAXGAP; j++){
			dp[i][j] = 0;
		}
	}
	for(int i = 0; i <= MAXGAP; i++) psum[i] = 0;

	// DP: base case
	int delta = a - b;
	int left = i0 + delta - 2*k;
	int right = i0 + delta + 2*k;
	for(int i = left; i <= right; i++){
		for(int A = -k; A <= k; A++){
			int B = delta + A - (i - i0);
			if(-k <= B && B <= k) dp[0][i] += 1;
		}
	}

	// DP: recursive case
	int left_prev, right_prev;
	for(int i = 1; i < t; i++){
		// calculate previous partial sum
		left_prev = left; right_prev = right;
		//psum[left_prev] = dp[i-1][left_prev];
		psum[0] = dp[i-1][0];
		for(int j = 1; j <= MAXGAP ; j++){
			psum[j] = dp[i-1][j] + psum[j-1];
		}
		// calculate dp[i][j]
		left = max(0, left - 2*k);
		right = min(MAXGAP, right + 2*k);
		//left = 0; right = MAXGAP;
		for(int j = left; j <= right; j++){
			dp[i][j] = (j-1 >= 0) ? dp[i][j-1] : 0;
			dp[i][j] += partialSum(j, j + 2*k, left_prev, right_prev);
			dp[i][j] -= partialSum(j - 2*k - 1, j - 1, left_prev, right_prev);
		}
		for(int j = left; j <= right; j++){
			dp[i][j] = dp[i][j] % MOD;
		}
	}

	// output
	long long int soln = 0;
	for(int j = i0 + 1; j <= MAXGAP; j++){
		soln = (soln + dp[t-1][j]) % MOD;
	}
	cout << soln << endl;

	return 0;
}
