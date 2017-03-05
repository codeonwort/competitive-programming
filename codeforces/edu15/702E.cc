// ID:  702E (Analysis of Pathes in Functional Graph)
// URL: http://codeforces.com/problemset/problem/702/E

#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 100000;
int weight[MAX], conn[MAX];

// dp[i][j].to:     starting from node i, after 2^j iterations, where am I?
// dp[i][j].cost:   path's cost
// dp[i][j].weight: minimum weight in the path
struct node {
	int to;
	long long int cost;
	int minWeight;
};
node dp[MAX][60];

int main() {
	int n;
	long long int goal;

	// input
	cin >> n >> goal;
	for(int i=0; i<n; i++) scanf("%d", conn + i);
	for(int i=0; i<n; i++) scanf("%d", weight + i);

	// DP: base case
	for(int i=0; i<n; i++){
		dp[i][0].to = conn[i];
		dp[i][0].cost = weight[i];
		dp[i][0].minWeight = weight[i];
	}

	// DP: recursive case
	for(int j=1; j<60; j++){
		for(int i=0; i<n; i++){
			int mid = dp[i][j-1].to;
			dp[i][j].to = dp[mid][j-1].to;
			dp[i][j].cost = dp[i][j-1].cost + dp[mid][j-1].cost;
			dp[i][j].minWeight = min(dp[i][j-1].minWeight, dp[mid][j-1].minWeight);
		}
	}

	// output
	for(int i=0; i<n; i++){
		// print s_i and m_i
		long long int k = goal;
		int j = 0;
		long long int s = 0;
		int m = 1e8 + 1;
		int from = i;
		while(k){
			if(k & 1){
				s += dp[from][j].cost;
				m = min(m, dp[from][j].minWeight);
				from = dp[from][j].to;
			}
			k = k >> 1;
			j++;
		}
		cout << s << ' ' << m << endl;
	}

	return 0;
}
