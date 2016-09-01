// ID:	1463 (1로 만들기)
// URL:	https://www.acmicpc.net/problem/1463

#include <iostream>
#include <algorithm>

using namespace std;

int solve(int n) {
	// dp[i]: min num of operations to make i -> 1
	int dp[1000001];

	dp[1] = 0;

	for(int i=2; i<=n; i++){
		dp[i] = dp[i-1] + 1;
		if(i % 2 == 0) dp[i] = min(dp[i], dp[i/2]+1);
		if(i % 3 == 0) dp[i] = min(dp[i], dp[i/3]+1);
	}

	return dp[n];
}

int main() {
	int n; // 1 <= n <= 1e6

	// input
	cin >> n;

	// solve
	int cnt = solve(n);
	cout << cnt << endl;
	
	return 0;
}

