// ID:  JUMPGAME
// URL: https://algospot.com/judge/problem/read/JUMPGAME

#include <iostream>
using namespace std;

int jump[100][100];
bool dp[100+10][100+10];

void solve();

int main() {
	int c;
	cin >> c;
	while(c --> 0) solve();
	return 0;
}

void solve() {
	int n;
	cin >> n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin >> jump[i][j];
			dp[i][j] = false;
		}
	}

	// DP
	dp[0][0] = true;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(dp[i][j] == false) continue;
			if(i == n-1 && j == n-1) continue;
			int a = jump[i][j];
			dp[i+a][j] = true;
			dp[i][j+a] = true;
		}
	}

	bool possible = dp[n-1][n-1];
	if(possible) cout << "YES" << endl;
	else cout << "NO" << endl;
}

