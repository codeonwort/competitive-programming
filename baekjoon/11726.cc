// ID:  11726 (2xn 타일링)
// URL: https://www.acmicpc.net/problem/11726

#include <iostream>
#define LL long long

using namespace std;

int main() {
	int n;
	LL dp[10001];

	// input
	cin >> n;

	// DP
	dp[0] = 0;
	dp[1] = 1;
	dp[2] = 2;
	for(int i=3; i<=n; i++){
		dp[i] = dp[i-1] + dp[i-2];
		dp[i] = dp[i] % 10007;
	}

	// output
	LL soln = dp[n];
	cout << soln << endl;

	return 0;
}
