// ID:  FAMILYTREE (족보 탐험)
// URL: https://algospot.com/judge/problem/read/FAMILYTREE

#include <stdio.h>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int parents[100000];
int posInOrder[100000];
int depth[100000];

struct SegTree {
	int minBound, maxBound;
	int minDepth;
	SegTree *left, *right;
	void build(int minBnd, int maxBnd, vector<int>& postorder) {
		minBound = minBnd; maxBound = maxBnd;
		if(minBnd == maxBnd){
			left = right = nullptr;
			minDepth = depth[postorder[minBound]];
		}else{
			left = new SegTree;
			right = new SegTree;
			int mid = (minBnd + maxBnd) / 2;
			left->build(minBnd, mid, postorder);
			right->build(mid+1, maxBnd, postorder);
			minDepth = min(left->minDepth, right->minDepth);
		}
	}
	int query(int l, int r) {
		if(l <= minBound && maxBound <= r) return minDepth;
		else if(maxBound < l || r < minBound) return 1e8;
		return min(left->query(l, r), right->query(l, r));
	}
};

int pos;
void dfs(int v, int d, map< int, vector<int> >& links, vector<int>& order) {
	vector<int>& children = links[v];
	order.push_back(v);
	posInOrder[v] = pos;
	depth[v] = d;
	pos++;
	for(int i=0; i<children.size(); i++){
		dfs(children[i], d+1, links, order);
		order.push_back(v);
		pos++;
	}
}

void solve() {
	int n, q;
	scanf("%d %d", &n, &q);

	parents[0] = -1;
	for(int i=1; i<n; i++) scanf("%d", parents + i);

	map< int, vector<int> > links;
	for(int i=1; i<n; i++){
		int child = i, parent = parents[i];
		links[parent].push_back(child);
	}

	// get postorder traversal
	vector<int> postorder;
	pos = 0;
	dfs(0, 0, links, postorder);

	// build segment tree
	depth[0] = 0;
	SegTree tree;
	tree.build(0, postorder.size()-1, postorder);

	// queries
	while(q --> 0){
		int a, b;
		scanf("%d %d", &a, &b);
		int u = depth[a], v = depth[b];
		a = posInOrder[a];
		b = posInOrder[b];
		if(a > b){ int temp = a; a = b; b = temp; }
		int uv = tree.query(a, b);
		int cost = u + v - uv * 2;
		printf("%d\n", cost);
	}
}

int main() {
	int t;
	scanf("%d", &t);
	while(t --> 0) solve();
	return 0;
}
