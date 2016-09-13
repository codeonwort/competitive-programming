// ID:  712A (Memory and Crow)
// URL: http://codeforces.com/problemset/problem/712/A

#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	long long n, A[100000], B[100000];

	// input
	scanf("%d", &n);
	for(int i=0; i<n; i++) scanf("%d", A + i);

	// run DP
	B[n-1] = A[n-1];
	for(int i=n-2; i>=0; i--){
		B[i] = A[i] + A[i+1];
	}

	// output
	for(int i=0; i<n; i++) printf("%d ", B[i]);

	return 0;
}
