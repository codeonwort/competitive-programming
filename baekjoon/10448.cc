#include <iostream>
#include <vector>

using namespace std;

// ID:	10448 (유레카 이론)
// URL:	https://www.acmicpc.net/problem/10448

void solve();

int main() {
	int t;
	
	cin >> t;
	while(t --> 0) solve();

	return 0;
}

void solve() {
	int goal;
	vector<int> ns;

	cin >> goal;

	int n = 1;
	while(true){
		int m = n * (n+1) / 2;
		if(m >= goal) break;
		ns.push_back(m);
		n++;
	}

	n = ns.size();
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			for(int k=0; k<n; k++){
				if(ns[i]+ns[j]+ns[k] == goal){
					cout << 1 << endl;
					return;
				}
			}
		}
	}

	cout << 0 << endl;
}
