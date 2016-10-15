// ID:  FORTRESS (요새)
// URL: https://algospot.com/judge/problem/read/FORTRESS

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct circle {
	int x, y, r;
	vector<circle> children;
	circle(int x, int y, int r):x(x), y(y), r(r) {}
	int getMaxDepth() {
		if(children.size() == 0) return 1;
		int depth = 0;
		for(int i=0; i<children.size(); i++){
			depth = max(depth, children[i].getMaxDepth());
		}
		return depth + 1;
	}
	void add(circle& child) {
		for(int i=0; i<children.size(); i++){
			if(children[i].contains(child)){
				children[i].add(child);
				return;
			}
		}
		children.push_back(child);
	}
	bool contains(circle& child) {
		// assume r >= child.r
		int dx = x - child.x, dy = y - child.y, dr = r - child.r;
		return dx*dx + dy*dy < dr*dr;
	}
	int longest() {
		// find the longest path
		vector<int> depths;
		for(int i=0; i<children.size(); i++){
			depths.push_back(children[i].getMaxDepth());
		}
		sort(depths.begin(), depths.end());
		int fst = depths.size() ? depths[depths.size()-1] : 0;
		int snd = depths.size() >= 2 ? depths[depths.size()-2] : 0;
		return fst + snd;
	}
};
bool compRadii(const circle& a, const circle& b) { return a.r > b.r; }

/*void print(circle& C, string pre) {
	cout << pre << "(" << C.x << " " << C.y << " " << C.r << ")" << endl;
	for(int i=0; i<C.children.size(); i++){
		print(C.children[i], pre + " ");
	}
}*/

int dfs(circle& C) {
	int longest = C.longest();
	for(int i=0; i<C.children.size(); i++){
		longest = max(longest, dfs(C.children[i]));
	}
	return longest;
}

void solve() {
	int n;
	cin >> n;

	// input
	vector<circle> circles;
	for(int i=0; i<n; i++){
		int x, y, r;
		cin >> x >> y >> r;
		circle C = {x, y, r};
		circles.push_back(C);
	}
	sort(circles.begin(), circles.end(), compRadii);

	// build the fortress
	circle root = circles[0];
	for(int i=1; i<circles.size(); i++){
		root.add(circles[i]);
	}

	// output
	int longest = dfs(root);
	cout << longest << endl;
}

int main() {
	int t;
	cin >> t;
	while(t --> 0) solve();
	return 0;
}
