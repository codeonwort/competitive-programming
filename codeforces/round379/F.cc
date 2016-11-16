// Codeforces Round #379 (Div. 2)
// http://codeforces.com/contest/734

// ID: 734F (Anton and School)

#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
const int MAX = 200000, MAX_BIT = 31;
int A[MAX], B[MAX], C[MAX]; // original
ll D[MAX]; // A: solution, D:temporary
int B2[MAX], C2[MAX]; // reconstructed (to be compared with original)
int BK[MAX][MAX_BIT], CK[MAX][MAX_BIT];
int K[MAX_BIT];

void solve() {
	// input
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++) scanf("%d", B + i);
	for(int i=0; i<n; i++) scanf("%d", C + i);
	for(int i=0; i<n; i++) D[i] = B[i] + C[i];
	memset(B2, 0, sizeof(B2));
	memset(C2, 0, sizeof(C2));
	memset(K, 0, sizeof(K));

	// find solution
	ll sumA = 0;
	for(int i=0; i<n; i++) sumA += D[i];
	sumA /= 2*n;
	for(int i=0; i<n; i++) A[i] = (D[i] - sumA) / n;

	// reconstruct
	for(int i=0; i<n; i++){
		for(int j=0; j<MAX_BIT; j++){
			if(A[i] & (1 << j)) K[j] += 1;
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<MAX_BIT; j++){
			int a = A[i] & (1 << j); if(a >= 1) a = 1;
			BK[i][j] = a == 0 ? 0 : K[j];
			CK[i][j] = a == 0 ? K[j] : n;
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<MAX_BIT; j++){
			B2[i] += BK[i][j] * (1 << j);
			C2[i] += CK[i][j] * (1 << j);
		}
	}

	// output
	for(int i=0; i<n; i++){
		if(B[i] != B2[i] || C[i] != C2[i]){
			puts("-1"); return;
		}
	}
	for(int i=0; i<n; i++){
		printf("%d ", A[i]);
	}
	puts("");
}

int main() {
	solve();
	return 0;
}
