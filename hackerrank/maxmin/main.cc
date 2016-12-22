// HackerRank.com
// ID:  Max Min
// URL: https://www.hackerrank.com/challenges/angry-children

#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAX = 100000;
int A[MAX];

/*
 * Why I wrote this? It's a sorted array!
 * Epic stupid
struct SegTree {
	SegTree *left, *right;
	int L, R;
	int minValue, maxValue;
	SegTree(int l, int r) {
		L = l; R = r;
		if(l == r){
			left = nullptr;
			right = nullptr;
			minValue = maxValue = A[l];
		}else{
			int mid = (l + r) / 2;
			left = new SegTree(l, mid);
			right = new SegTree(mid+1, r);
			minValue = min(left->minValue, right->minValue);
			maxValue = max(left->maxValue, right->maxValue);
		}
	}
	int queryMin(int l, int r) {
		if(l <= L && R <= r) return minValue;
		else if(R < l || r < L) return 1e9;
		return min(left->queryMin(l, r), right->queryMin(l, r));
	}
	int queryMax(int l, int r) {
		if(l <= L && R <= r) return maxValue;
		else if(R < l || r < L) return 0;
		return max(left->queryMax(l, r), right->queryMax(l, r));
	}
};
*/

void solve() {
	int n, k;
	scanf("%d %d", &n, &k);
	for(int i=0; i<n; i++) scanf("%d", A + i);

	sort(A, A + n);
	//SegTree tree(0, n-1);

	int answer = 1e9;
	for(int i=0; i<n; i++){
		int j = i + k - 1;
		if(j >= n) break;
		//int x = tree.queryMax(i, j) - tree.queryMin(i, j);
		int x = A[j] - A[i];
		answer = min(answer, x);
	}

	printf("%d\n", answer);
}

int main() {
	solve();
	return 0;
}
