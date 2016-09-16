// ID:  714A (Meeting of Old Friends)
// URL: a

//#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define LL long long

int main() {
	LL l1,r1, l2,r2, k;

	cin >> l1 >> r1 >> l2 >> r2 >> k;

	if(l1 > r2 || r1 < l2){
		cout << 0 << endl;
		return 0;
	}

	LL dist, left, right;
	if(l2 <= l1 && r1 <= r2){
		dist = r1 - l1 + 1;
		if(l1 <= k && k <= r1) dist--;
	}else if(l1 <= l2 && r2 <= r1){
		dist = r2 - l2 + 1;
		if(l2 <= k && k <= r2) dist--;
	}else{
		dist = min(r1 - l2 + 1, r2 - l1 + 1);
		left = max(l1, l2);
		right = min(r1, r2);
		if(left <= k && k <= right) dist--;
	}

	cout << dist << endl;

	return 0;
}
