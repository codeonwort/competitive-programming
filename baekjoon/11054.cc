// ID:  11054 (가장 긴 바이토닉 부분 수열)
// URL: https://www.acmicpc.net/problem/11054
// Category: Data Structure, Dynamic Programming

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int bitonic(vector<int>& xs) {
	int n = xs.size();
	vector<int> lis(n, 987654321), lis2(n, 987654321);
	vector<int> maxLen(n), maxLen2(n);

	for(int i=0; i<n; i++){
		int j = lower_bound(lis.begin(), lis.end(), xs[i]) - lis.begin();
		lis[j] = xs[i];
		maxLen[i] = j;
	}
	for(int i=n-1; i>=0; i--){
		int j = lower_bound(lis2.begin(), lis2.end(), xs[i]) - lis2.begin();
		lis2[j] = xs[i];
		maxLen2[i] = j;
	}

	int len = 0;
	for(int i=0; i<n; i++){
		len = max(len, maxLen[i] + maxLen2[i]);
	}

	return len + 1;
}

int main() {
	int n;
	cin >> n;

	vector<int> xs(n);
	for(int i=0; i<n; i++) cin >> xs[i];

	cout << bitonic(xs) << endl;

	return 0;
}
