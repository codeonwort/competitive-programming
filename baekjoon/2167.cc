// ID:  2167 (2차원 배열의 합)
// URL: https://www.acmicpc.net/problem/2167

#include <iostream>
#define LL long long

using namespace std;

int main() {
	int n,m; // matrix size
	LL matrix[301][301]; // start from (1,1)
	
	// input
	cin >> n >> m;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			cin >> matrix[i][j];
		}
	}

	// sum[i][j]: block sum of matrix from (1,1) to (i,j)
	LL sum[301][301]; // start from (1,1)

	// initial solution
	for(int i=0; i<=n; i++){
		sum[0][i] = 0;
		sum[i][0] = 0;
	}

	// DP
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			sum[i][j] = sum[i][j-1] + sum[i-1][j] - sum[i-1][j-1] + matrix[i][j];
		}
	}

	int k; // number of queries
	cin >> k;

	while(k --> 0){
		int top,left, bottom,right;
		cin >> top >> left >> bottom >> right;

		LL soln = sum[bottom][right];
		soln -= sum[top-1][right] + sum[bottom][left-1];
		soln += sum[top-1][left-1];
		cout << soln << endl;
	}

	return 0;
}
