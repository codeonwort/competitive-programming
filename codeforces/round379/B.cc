// Codeforces Round #379 (Div. 2)
// http://codeforces.com/contest/734

// ID: 734B (Anton and Digits)

#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
	int k2, k3, k5, k6;
	cin >> k2 >> k3 >> k5 >> k6;

	long long int sum = 0;
	while(true){
		bool update = false;
		if(k2 >= 1 && k5 >= 1 && k6 >= 1){
			sum += 256;
			k2--; k5--; k6--;
			update = true;
		}
		if(!update) break;
	}
	while(true){
		bool update = false;
		if(k3 >= 1 && k2 >= 1){
			sum += 32;
			k3--; k2--;
			update = true;
		}
		if(!update) break;
	}

	cout << sum << endl;
}

int main() {
	solve();
	return 0;
}
