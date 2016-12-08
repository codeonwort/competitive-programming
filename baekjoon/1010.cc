// ID:  1010 (다리 놓기)
// URL: https://www.acmicpc.net/problem/1010

#include <iostream>
using namespace std;

typedef long long ll;

ll dp[30][30];

void init() {
	dp[0][0] = 0;
	for(int i=1; i<30; i++) dp[i][0] = dp[0][i] = 1;
	for(int i=1; i<30; i++){
		for(int j=1; j<=i; j++){
			dp[i][j] = dp[i-1][j] + dp[i-1][j-1];
		}
	}
}

void solve() {
	int n, m;
	cin >> n >> m;
	cout << dp[m][n] << endl;
}

int main() {
	int t;
	cin >> t;
	init();
	while(t --> 0) solve();
	return 0;
}
