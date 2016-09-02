// ID:  9461 (파도반 수열)
// URL: https://www.acmicpc.net/problem/9461

#include <iostream>
#define LL long long

using namespace std;

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

	// DP
	LL dp[101];
	dp[1] = dp[2] = dp[3] = 1;
	for(int i=4; i<=n; i++){
		dp[i] = dp[i-2] + dp[i-3];
	}

	// output
	LL soln = dp[n];
	cout << soln << endl;
}
