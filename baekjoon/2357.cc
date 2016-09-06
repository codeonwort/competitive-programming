// ID:  2357 (최소값과 최대값)
// URL: https://www.acmicpc.net/problem/2357

#include <stdio.h>
#include <algorithm>
#define INF 1000000001
using namespace std;

int nums[100000];

// segment tree implementation
struct segTree {
	segTree *left, *right; // child nodes
	int minIx, maxIx; // bounds
	int minimum, maximum; // values

	void build(int nums[], int l, int r) {
		// base case
		if(l == r){
			minIx = maxIx = l;
			minimum = maximum = nums[l];
			return;
		}

		// divide
		int mid = (l+r)/2;
		left = new segTree;
		right = new segTree;
		left->build(nums, l, mid);
		right->build(nums, mid+1, r);

		// conquer
		minIx = l; maxIx = r;
		minimum = min(left->minimum, right->minimum);
		maximum = max(left->maximum, right->maximum);
	}
	int findMin(int l, int r) {
		if(maxIx < l || r < minIx) return INF;
		if(l <= minIx && maxIx <= r) return minimum;
		return min(left->findMin(l, r), right->findMin(l, r));
	}
	int findMax(int l, int r) {
		if(maxIx < l || r < minIx) return -1;
		if(l <= minIx && maxIx <= r) return maximum;
		return max(left->findMax(l, r), right->findMax(l, r));

	}
};

int main() {
	int n, m;

	scanf("%d%d", &n, &m);
	for(int i=0; i<n; i++) scanf("%d", nums+i);

	segTree root;
	root.build(nums, 0, n-1);

	int left, right;
	for(int i=0; i<m; i++){
		scanf("%d%d", &left, &right);
		left--; right--;
		int a = root.findMin(left, right);
		int b = root.findMax(left, right);
		printf("%d %d\n", a, b);
	}

	return 0;
}
