// ID:  356A (Knight Tournament)
// URL: http://codeforces.com/problemset/problem/356/A
// Category: Segment Tree

#include <stdio.h>
#include <string.h>
using namespace std;

const int MAX = 3 * 100000;
int defeater[MAX];

struct SegTree {
	int L, R;
	SegTree *left, *right;
	bool empty;
	SegTree(int l, int r):L(l), R(r), empty(false) {}
	void build() {
		if(L == R){
			left = right = nullptr;
		}else{
			int mid = (L + R) / 2;
			left = new SegTree(L, mid);
			right = new SegTree(mid+1, R);
			left->build();
			right->build();
		}
	}
	void update(int l, int r, int x) {
		if(r < L || R < l){
			return;
		}
		if(empty) return;
		if(left || right){
			left->update(l, r, x);
			right->update(l, r, x);
			if(left->empty && right->empty) empty = true;
		}else if(L != x){
			defeater[L] = x + 1;
			empty = true;
		}
	}
};

int main() {
	int n, m;
	scanf("%d %d", &n, &m);

	// solve
	SegTree tree(0, n-1);
	tree.build();
	memset(defeater, 0, sizeof(defeater));
	for(int i=0; i<m; i++){
		int l, r, x;
		scanf("%d %d %d", &l, &r, &x);
		l--; r--; x--;
		tree.update(l, r, x);
	}

	// output
	for(int i=0; i<n; i++) printf("%d ", defeater[i]);
	puts("");

	return 0;
}
