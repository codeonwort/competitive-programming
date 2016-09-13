// ID:  712B (Memory and Trident)
// URL: http://codeforces.com/problemset/problem/712/B

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main() {
	string s;
	int L=0, R=0, U=0, D=0;

	cin >> s;

	bool impossible = s.size() & 1;
	if(impossible){
		cout << -1 << endl;
		return 0;
	}

	char c;
	for(int i=0; i<s.size(); i++){
		c = s[i];
		if(c == 'L') L++;
		else if(c == 'R') R++;
		else if(c == 'U') U++;
		else if(c == 'D') D++;
	}

	int dx = abs(R-L);
	int dy = abs(U-D);

	int step = 1e8;
	bool bothEven = !(dx&1) && !(dy&1);
	bool bothOdd = (dx&1) && (dy&1);
	if(bothEven || bothOdd){
		step = min(dx,dy) + (max(dx,dy)-min(dx,dy))/2;
	}
	if(step == 1e8) step = -1;
	cout << step << endl;

	return 0;
}
