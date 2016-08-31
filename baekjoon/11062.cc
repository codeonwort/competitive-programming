#include <iostream>
#include <algorithm>

// ID:	11062 (카드 게임)
// URL:	https://www.acmicpc.net/problem/11062

using namespace std;

void solve();

int main() {
	int t;

	cin >> t;

	while(t --> 0) solve();

	return 0;
}

struct soln {
	int card;
	int score;
};

void solve() {
	// dp[i][j]: best score with cards[i..j]
	soln dp[1001][1001];
	int cards[1001];
	int n;

	cin >> n;

	for(int i=0; i<n; i++){
		cin >> cards[i];
	}

	// initial solution
	for(int i=0; i<n; i++){
		dp[i][i].card = i;
		dp[i][i].score = cards[i];
	}
	for(int i=0; i<n-1; i++){
		if(cards[i] > cards[i+1]){
			dp[i][i+1].card = i;
			dp[i][i+1].score = cards[i];
		}else{
			dp[i][i+1].card = i+1;
			dp[i][i+1].score = cards[i+1];
		}
	}

	// do DP
	int j0 = 2;
	for(int k=n-2; k>0; k--){
		for(int i=0; i<k; i++){
			int j = i + j0;
			// dp[i][j]: you can take i-th or j-th card
			int pickLeft = cards[i];
			if(dp[i+1][j].card == i+1) pickLeft += dp[i+2][j].score;
			else pickLeft += dp[i+1][j-1].score;

			int pickRight = cards[j];
			if(dp[i][j-1].card == i) pickRight += dp[i+1][j-1].score;
			else pickRight += dp[i][j-2].score;

			if(pickLeft > pickRight){
				dp[i][j].card = i;
				dp[i][j].score = pickLeft;
			}else{
				dp[i][j].card = j;
				dp[i][j].score = pickRight;
			}
		}
		j0++;
	}

	/*cout << "dp====" << endl;
	for(int i=0; i<n; i++){
		int j;
		for(j=0; j<i; j++) cout << "x ";
		for(; j<n; j++) cout << dp[i][j].score << ' ';
		cout << endl;
	}*/

	int answer = dp[0][n-1].score;
	cout << answer << endl;
}

