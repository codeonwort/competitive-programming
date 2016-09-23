// ID:  545C (Woodcutters)
// URL: http://codeforces.com/problemset/problem/545/C

#include <iostream>
#include <algorithm>
using namespace std;

struct wood {
	int x;
	int height;
	int left, right;
};
bool compareWood(const wood& a, const wood& b) {
	return a.x < b.x;
}

wood woods[100000];
int dp[100000][3];

int main() {
	int n;

	// input
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> woods[i].x >> woods[i].height;
		woods[i].left = woods[i].x - woods[i].height;
		woods[i].right = woods[i].x + woods[i].height;
	}
	sort(woods, woods + n, compareWood);

	// special case
	if(n == 1){
		cout << 1 << endl;
		return 0;
	}

	// DP: base case
	dp[0][0] = 0;
	dp[0][1] = dp[0][2] = 1;

	// DP: recursive case
	for(int i=1; i<n; i++){
		// i-th tree does not fall
		dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
		if(woods[i-1].right < woods[i].x){
			dp[i][0] = max(dp[i][0], dp[i-1][2]);
		}
		// i-th tree falls to left
		if(woods[i].left <= woods[i-1].x) dp[i][1] = 0;
		else{
			dp[i][1] = max(dp[i-1][0] + 1, dp[i-1][1] + 1);
			if(woods[i].left > woods[i-1].right){
				dp[i][1] = max(dp[i][1], dp[i-1][2] + 1);
			}
		}
		// i-th tree falls to right
		dp[i][2] = max(dp[i-1][0], dp[i-1][1]) + 1;
		if(woods[i-1].right < woods[i].x){
			dp[i][2] = max(dp[i][2], dp[i-1][2] + 1);
		}
	}

	// output
	int soln = max(max(dp[n-1][0], dp[n-1][1]), dp[n-1][2]);
	cout << soln << endl;

	return 0;
}
