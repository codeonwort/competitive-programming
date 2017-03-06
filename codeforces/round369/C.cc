// ID:  711C (Coloring Trees)
// URL: http://codeforces.com/problemset/problem/711/C

#include <stdio.h>
#include <limits.h>
#include <algorithm>

using namespace std;

#define LL long long
#define popNewline(x) scanf("%c", &x);
#define infinity 1e18L

int main() {
	///////////////////////////////////////
	// variables
	int n, m, k;
	int colors[101]; // start from index 1
	LL costs[101][101]; // start from index (1,1)
	char dummy;

	///////////////////////////////////////
	// input
	scanf("%d%d%d", &n, &m, &k);
	popNewline(dummy);

	for(int i=1; i<=n; i++){
		scanf("%d", &colors[i]);
	}
	popNewline(dummy);

	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			scanf("%lld", &costs[i][j]);
		}
		popNewline(dummy);
	}

	///////////////////////////////////////
	// solve
	// dp[i][j][k]: min cost to fill first i trees with beauty j
	//              where k = (color of i-th tree)
	LL dp[101][101][101];

	for(int i=0; i<101; i++){
		for(int j=0; j<101; j++){
			for(int a=0; a<101; a++) dp[i][j][a] = infinity;
		}
	}

	// initial values: cost to fill the first tree
	if(colors[1] == 0){
		for(int i=1; i<=m; i++) dp[1][1][i] = costs[1][i];
	}else{
		dp[1][1][colors[1]] = 0;
	}
	
	// calculate DP table
	for(int i=2; i<=n; i++){
		for(int j=1; j<=k; j++){
			if(colors[i] == 0){
				for(int a=1; a<=m; a++){
					dp[i][j][a] = min(dp[i][j][a], dp[i-1][j][a] + costs[i][a]);
					for(int b=1; b<=m; b++){
						if(b != a) dp[i][j][a] = min(dp[i][j][a], dp[i-1][j-1][b] + costs[i][a]);
					}
				}
			}else{
				dp[i][j][colors[i]] = min(dp[i][j][colors[i]], dp[i-1][j][colors[i]]);
				for(int b=1; b<=m; b++){
					if(b != colors[i]) dp[i][j][colors[i]] = min(dp[i][j][colors[i]], dp[i-1][j-1][b]);
				}
			}
		}
	}

	LL soln = infinity;
	for(int i=1; i<=m; i++){
		soln = min(soln, dp[n][k][i]);
	}
	if(soln == infinity) puts("-1");
	else printf("%lld\n", soln);

	return 0;
}
