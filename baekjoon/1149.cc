// ID:	1149 (RGB거리)
// URL:	https://www.acmicpc.net/problem/1149

#include <iostream>
#include <algorithm>
#define LL long long

using namespace std;

struct cost {
	LL red;
	LL green;
	LL blue;
};

int main() {
	int n; // number of houses
	cost costs[1000]; // n <= 1000

	// input
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> costs[i].red >> costs[i].green >> costs[i].blue;
	}

	// solve
	// dp[i]: min cost to fill 0 ~ i houses
	//        where i-th house is filled with each color
	cost dp[1000];

	// init soln
	dp[0].red = costs[0].red;
	dp[0].green = costs[0].green;
	dp[0].blue = costs[0].blue;

	// DP
	for(int i=1; i<n; i++){
		dp[i].red = min(dp[i-1].green, dp[i-1].blue) + costs[i].red;
		dp[i].green = min(dp[i-1].red, dp[i-1].blue) + costs[i].green;
		dp[i].blue = min(dp[i-1].green, dp[i-1].red) + costs[i].blue;
	}
	LL soln = min(dp[n-1].red, dp[n-1].green);
	soln = min(soln, dp[n-1].blue);

	cout << soln << endl;
}
