// ID:  691D (Swaps in Permutation)
// URL: http://codeforces.com/problemset/problem/691/D

#include <stdio.h>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
using namespace std;

struct node {
	int value;
	int idx;
};

int parent[1000001];
int result[1000001];
vector<node> nums;

void weightedUnion(int i, int j); // union (i, j should be roots)
int collapsingFind(int i); // find

bool comp(int x, int y) { return nums[x].value > nums[y].value; } // compare group elements

int main() {
	int n, m;

	scanf("%d %d", &n, &m);
	nums.resize(n);
	for(int i=0; i<n; i++){
		scanf("%d", &nums[i].value);
		nums[i].idx = i;
		parent[i] = -1;
	}

	// construct disjoint sets
	int a, b, root_a, root_b;
	for(int i=0; i<m; i++){
		scanf("%d %d", &a, &b);
		a--; b--;
		root_a = collapsingFind(a);
		root_b = collapsingFind(b);
		if(root_a == root_b){
			// it's a trap input
			// we don't need to union two elements in the same tree
			// ex: (i,j) = (1,1) -> root(i) == root(j)
			//     primarily, i == j in this case
			continue;
		}
		int ai = nums[a].idx, bi = nums[b].idx;
		weightedUnion(root_a, root_b);
	}

	// for each root R, make a group of nodes whose root is R
	vector<int> roots;
	map< int, vector<int> > forest;
	for(int i=0; i<n; i++){
		if(parent[i] < 0){
			roots.push_back(i);
		}
		int root = collapsingFind(i);
		if(forest.find(root) == forest.end()){
			forest.insert(make_pair(root, vector<int>()));
		}
		forest.find(root)->second.push_back(i);
	}

	// sort the nodes in same tree by their values
	for(int i=0; i<roots.size(); i++){
		vector<int> group = forest.find(roots[i])->second;
		vector<int> indices;
		// I think I should have separated the 'node' struct
		// into values[] and indices[]. this is unnecessary duplication of data.
		// well, this code fits in time. maybe optimize it later... permanantly.
		for(int j=0; j<group.size(); j++){
			indices.push_back(nums[group[j]].idx);
		}
		sort(group.begin(), group.end(), comp);
		for(int j=0; j<group.size(); j++){
			node& x = nums[group[j]];
			result[indices[j]] = x.value;
		}
	}

	// output
	for(int i=0; i<n; i++) printf("%d ", result[i]);
	puts("");

}

// union-find of disjoint sets ////////////////////////////
void weightedUnion(int i, int j) {
	int temp = parent[i] + parent[j];
	if(parent[i] < parent[j]){
		// i is begger
		parent[j] = i;
		parent[i] = temp;
	}else{
		// j is bigger
		parent[i] = j;
		parent[j] = temp;
	}
}

int collapsingFind(int i) {
	int root, tail;
	for(root = i; parent[root] >= 0; root = parent[root]);
	for(tail = i; tail != root; tail = parent[tail]){
		parent[tail] = root;
	}
	return root;
}
