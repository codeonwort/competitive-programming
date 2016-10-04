// ID:  723C (Polycarp at the Radio)
// URL: http://codeforces.com/contest/723/problem/C

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	// input
	int n, m;
	cin >> n >> m;
	vector<int> performers(n);
	for(int i=0; i<n; i++){
		cin >> performers[i];
	}

	// solve
	int goal = n / m;				// # of performs all good bands have to do
	int minChanges = 0;				// # of changes have to be made
	vector<int> goodPerforms(m);	// # of performs of good bands
	vector<int> notEnough;			// good bands that need more performs

	// find good performs
	for(int i=0; i<n; i++){
		int performer = performers[i];
		if(1 <= performer && performer <= m){
			goodPerforms[performer-1] += 1;
		}
	}
	for(int i=0; i<m; i++){
		if(goodPerforms[i] < goal){
			notEnough.push_back(i);
		}
	}

	// change performer
	for(int i=0; i<n, notEnough.size() > 0; i++){
		int p = performers[i];
		if(p <= m && goodPerforms[p-1] <= goal) continue;

		int need = notEnough.back();

		if(p <= m) goodPerforms[p-1] -= 1;
		goodPerforms[need]++;
		performers[i] = need + 1;
		if(goodPerforms[need] == goal){
			notEnough.pop_back();
		}

		minChanges++;
	}

	// output
	cout << goal << ' ' << minChanges << endl;
	for(int i=0; i<n; i++) cout << performers[i] << ' ';
	cout << endl;

	return 0;
}
