#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#define INF 987654321
int dp[10001];

int cost(string& s, int l, int r) {
	if(r-l < 2 || 4 < r-l) return INF;

	// minimum cost of s[l..r]
	bool ok;

	// 1. all same
	ok = true;
	for(int i=l+1; i<=r; i++){
		if(s[i] != s[l]){ ok = false; break; }
	}
	if(ok) return 1;
	
	// 2. inc
	ok = true;
	for(int i=l+1; i<=r; i++){
		if(s[i] != s[i-1]+1){ ok = false; break; }
	}
	if(ok) return 2;

	// 3. dec
	ok = true;
	for(int i=l+1; i<=r; i++){
		if(s[i] != s[i-1]-1) { ok = false; break; }
	}
	if(ok) return 2;

	// 4. interleave
	ok = true;
	for(int i=l+2; i<=r; i+=2){
		if(s[i] != s[l]){ ok = false; break; }
	}
	for(int i=l+3; i<=r; i+=2){
		if(s[i] != s[l+1]){ ok = false; break; }
	}
	if(ok) return 4;

	// 5. arithmetic seq
	ok = true;
	for(int i=l+2; i<=r; i++){
		if(s[i]-s[i-1] != s[l+1]-s[l]){
			ok = false; break;
		}
	}
	if(ok) return 5;

	// 6. otherwise
	return 10;
}

void solve() {
	int n;
	string str;

	cin >> str;
	n = str.size();

	// initial solution
	dp[0] = dp[1] = INF;
	dp[2] = cost(str, 0, 2); // slice size: 3
	dp[3] = cost(str, 0, 3); // slice size: 4
	dp[4] = cost(str, 0, 4); // slice size: 5

	// DP
	for(int i=5; i<n; i++){
		dp[i] = dp[i-3] + cost(str, i-2, i); // last slice size: 3
		if(i >= 6) dp[i] = min(dp[i], dp[i-4] + cost(str, i-3, i)); // last slice size: 4
		if(i >= 7) dp[i] = min(dp[i], dp[i-5] + cost(str, i-4, i)); // last slice size: 5
	}

	int soln = dp[n-1];
	cout << soln << endl;
}

int main() {
	int c;
	cin >> c;
	while(c --> 0) solve();
}
