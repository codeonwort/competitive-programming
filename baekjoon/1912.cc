// ID:  1912 (연속합)
// URL: https://www.acmicpc.net/problem/1912

#include <iostream>
#include <algorithm>
#define LL long long

using namespace std;

int main() {
	int n;
	LL xs[100000];

	// input
	cin >> n;
	for(int i=0; i<n; i++) cin >> xs[i];

	// DP
	LL bestSoFar, accum;

	// constraint: at least one element should be selected
	bestSoFar = accum = xs[0];

	for(int i=1; i<n; i++){
		accum = max(xs[i], accum + xs[i]);
		bestSoFar = max(bestSoFar, accum);
	}

	// output
	LL soln = bestSoFar;
	cout << soln << endl;

	return 0;
}
