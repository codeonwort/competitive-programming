// ID:  9599 (Equal Sum Sets)
// URL: https://www.acmicpc.net/problem/9599

#include <iostream>
#include <string.h>
using namespace std;

int dp[21][11][156];

int get(int i, int j, int k) {
	if(j == 0 && k == 0) return 1;
	if(i <= 0 || j <= 0 || k <= 0) return 0;
	return dp[i][j][k];
}

void solve(int n, int len, int sum) {
	memset(dp, 0, sizeof(dp));
	dp[1][1][1] = 1;

	for(int i=2; i<=n; i++){
		for(int j=1; j<=len; j++){
			for(int k=1; k<=sum; k++){
				//dp[i][j][k] = dp[i-1][j][k] + dp[i-1][j-1][k-i];
				dp[i][j][k] = get(i-1,j,k) + get(i-1,j-1,k-i);
			}
		}
	}

	cout << dp[n][len][sum] << endl;
}

int main() {
	while(true){
		int n,k,s;
		cin >> n >> k >> s;
		if(n == 0 && k == 0 && s == 0) break;
		solve(n, k, s);
	}
	return 0;
}
