// ID:  2163 (초콜릿 자르기)
// URL: https://www.acmicpc.net/problem/2163

#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;
ll dp[301][301];

int main() {
	int n, m;
	cin >> n >> m;

	dp[1][1] = 0;
	for(int i=2; i<=n; i++) dp[i][1] = i - 1;
	for(int j=2; j<=m; j++) dp[1][j] = j - 1;

	for(int i=2; i<=n; i++){
		for(int j=2; j<=m; j++){
			dp[i][j] = 1e18L;
			for(int k=1; k<i; k++){
				dp[i][j] = min(dp[i][j], dp[k][j] + dp[i-k][j] + 1);
			}
			for(int k=1; k<j; k++){
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[i][j-k] + 1);
			}
		}
	}

	ll answer = dp[n][m];
	cout << answer << endl;

	return 0;
}
