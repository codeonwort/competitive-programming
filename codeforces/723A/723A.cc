// ID:  723A (The New Year: Meeting Friends)
// URL: http://codeforces.com/problemset/problem/723/A

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int D(int x, int y) {
	return abs(x - y);
}

int main() {
	int a, b, c;

	cin >> a >> b >> c;

	vector<int> centers = {1, a, b, c, 100};
	int dist = 300;
	for(int i=0; i<centers.size(); i++){
		int center = centers[i];
		dist = min(dist, D(center,a) + D(center,b) + D(center,c));
	}
	cout << dist << endl;

	return 0;
}
