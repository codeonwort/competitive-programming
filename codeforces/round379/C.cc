// Codeforces Round #379 (Div. 2)
// http://codeforces.com/contest/734

// ID: 734C (Anton and Making Potions)

#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 2 * 1e5 + 1;
long long int A[MAX], B[MAX], C[MAX], D[MAX];

void solve() {
	long long int n; // num potions
	long long int m, k; // num spells of each type
	long long int x; // portion creation time
	long long int s; // manapoint usage limit
	cin >> n >> m >> k >> x >> s;

	for(int i=0; i<m; i++) scanf("%lld", A + i);
	for(int i=0; i<m; i++) scanf("%lld", B + i);
	for(int i=0; i<k; i++) scanf("%lld", C + i);
	for(int i=0; i<k; i++) scanf("%lld", D + i);

	// don't use first spell
	long long int best = 0;
	int freePotion = C[upper_bound(D, D+k, s) - D - 1];
	if(freePotion < n){
		best = (n - freePotion) * x;
	}

	// use first spell
	for(int i=0; i<m; i++){
		long long int cand = 0;
		long long int remain = n;
		long long int mana = s;
		if(B[i] > s) continue;
		// use first type spell
		mana -= B[i];
		// use second type spell
		int ub = upper_bound(D, D+k, mana) - D - 1;
		remain -= C[ub];
		if(remain > 0) cand += remain * A[i];
		best = min(best, cand);
	}

	cout << best << endl;
}

int main() {
	solve();
	return 0;
}
