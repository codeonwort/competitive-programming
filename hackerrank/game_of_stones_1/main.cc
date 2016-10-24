// ID:  Game of Stones
// URL: https://www.hackerrank.com/challenges/game-of-stones-1
// Category: Game Theory

#include <iostream>
using namespace std;

// dp[i]: there are i stones, player 1 chooses. will he win?
// dp2[i]: there are i stones, player 2 chooses. will he win?
bool dp[101], dp2[101];

void solve() {
	int n;
	cin >> n;

	dp[1] = dp2[1] = false;
	dp[2] = dp2[2] = true;
	dp[3] = dp2[3] = true;
	dp[4] = dp2[4] = true;
	dp[5] = dp2[5] = true;

	for(int i=6; i<=n; i++){
		dp[i] = !dp2[i-2] || !dp2[i-3] || !dp2[i-5];
		dp2[i] = !dp[i-2] || !dp[i-3] || !dp[i-5];
	}

	cout << (dp[n] ? "First" : "Second") << endl;
}

/* simpler solution
// dp[i]: there are i stones. Will the player who makes current turn win?
void solve() {
	int n;
	cin >> n;

	dp[1] = false;
	dp[2] = true;
	dp[3] = true;
	dp[4] = true;
	dp[5] = true;

	for(int i=6; i<=n; i++){
		dp[i] = !dp[i-2] || !dp[i-3] || !dp[i-5];
	}

	cout << (dp[n] ? "First" : "Second") << endl;
}
*/

int main() {
	int tests;
	cin >> tests;
	while(tests --> 0) solve();
	return 0;
}
