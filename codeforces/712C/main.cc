// ID:  713C (Memory and De-Evolution)
// http://codeforces.com/problemset/problem/712/C

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	int x, y;
	int a, b, c;

	// input
	cin >> x >> y;

	// special case
	if(x == y){
		cout << 0 << endl;
		return 0;
	}

	// solve (reverse)
	int step = 0;
	a = b = c = y;
	while(c != x){
		int d = min(x, b + c - 1);
		a = c; c = b ; b = d;

		vector<int> nums;
		nums.push_back(a);
		nums.push_back(b);
		nums.push_back(c);
		sort(nums.begin(), nums.end());
		a = nums[0]; b = nums[1]; c = nums[2];

		step++;

		// FUCK I submitted this code with this if statement enabled
		// if(step > 10) break;
	}
	if(a != x) step++;
	if(b != x) step++;

	// output
	cout << step << endl;

	return 0;
}
