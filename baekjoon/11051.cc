// ID:  11051 (이항 계수 2)
// URL: https://www.acmicpc.net/problem/11051

#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

int C[1001][1001];

void calc(int n, int k) {
	memset(C, 0, sizeof(C));
	for(int i=0; i<=n; i++) C[i][0] = 1;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=min(k,i); j++){
			if(i == j) C[i][j] = 1;
			else C[i][j] = C[i-1][j-1] + C[i-1][j];
		}
		for(int j=1; j<=k; j++){
			C[i][j] = C[i][j] % 10007;
		}
	}
}

int main() {
	int n,k;
	cin >> n >> k;
	calc(n,k);
	cout << C[n][k] << endl;
	return 0;
}
