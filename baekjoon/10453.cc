// ID:  10453 (문자열 변환)
// URL: https://www.acmicpc.net/problem/10453

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
	string a, b;
	cin >> a >> b;

	// special case: different lengths
	if(a.size() != b.size()){
		cout << -1 << endl;
		return;
	}

	// check the position of 'a' in each string
	int len = a.size();
	long long int swaps = 0;
	vector<int> a_inA, a_inB;
	for(int i=0; i<len; i++){
		if(a[i] == 'a') a_inA.push_back(i);
		if(b[i] == 'a') a_inB.push_back(i);
	}

	// special case 2: number of 'a' in two strings are different
	if(a_inA.size() != a_inB.size()){
		cout << -1 << endl;
		return;
	}

	// calculating number of swaps is very easy
	for(int i=0; i<a_inA.size(); i++){
		swaps += abs(a_inA[i] - a_inB[i]);
	}

	// but is it good transformation in entire steps?
	// yes, always.
	// and I don't know why the hell it is
	bool valid = true;

	// output
	if(!valid) swaps = -1;
	cout << swaps << endl;
}

int main() {
	int t;
	cin >> t;
	while(t --> 0) solve();
}
