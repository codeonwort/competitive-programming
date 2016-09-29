// ID:  2574 (마법색종이)
// URL: https://www.acmicpc.net/problem/2574

#include <iostream>
#include <algorithm>
using namespace std;

struct Tree {
	int x, y, w, h;
	bool white;
	Tree *left, *right;
	Tree(int x, int y, int w, int h, bool white): x(x), y(y), w(w), h(h), white(white) {
		left = nullptr;
		right = nullptr;
	}
	void add(int px, int py) {
		if(x <= px && px <= x + w && y <= py && py <= y + h){
			if(left || right){
				left->add(px, py);
				right->add(px, py);
			}else{
				if(white){
					left = new Tree(x, py, w, y+h-py, !white);
					right = new Tree(x, y, w, py-y, !white);
				}else{
					left = new Tree(x, y, px-x, h, !white);
					right = new Tree(px, y, x+w-px, h, !white);
				}
			}
		}
	}
	int size() { return w * h; }
	int findMin() {
		if(left || right) return min(left->findMin(), right->findMin());
		return size();
	}
	int findMax() {
		if(left || right) return max(left->findMax(), right->findMax());
		return size();
	}

};

int main() {
	int w, h, n;

	cin >> w >> h >> n;
	Tree root(0, 0, w, h, true);
	for(int i=0; i<n; i++){
		int x, y;
		cin >> x >> y;
		root.add(x, y);
	}

	cout << root.findMax() << ' ' << root.findMin() << endl;

	return 0;
}
