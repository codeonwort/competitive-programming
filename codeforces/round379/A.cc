// Codeforces Round #379 (Div. 2)
// http://codeforces.com/contest/734

// ID: 734A (Anton and Danik)

#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

void solve() {
	int n;
	string s;
	cin >> n >> s;

	int a = 0, d = 0;
	for(int i=0; i<n; i++){
		if(s[i] == 'A') a++;
		else d++;
	}

	if(a > d) cout << "Anton" << endl;
	else if(a < d) cout << "Danik" << endl;
	else cout << "Friendship" << endl;
}

int main() {
	solve();
	return 0;
}
