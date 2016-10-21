// ID:  10999 (구간 합 구하기 2)
// URL: https://www.acmicpc.net/problem/10999
// Category: Segment Tree (Range Update)

#include <stdio.h>
#include <algorithm>
using namespace std;

typedef long long int LL;
const int MAX = 1000000;
LL num[MAX];

struct SegTree {
	SegTree *left, *right;
	int L, R;
	LL sum, acc;
	SegTree():acc(0) {}
	void build(int l, int r) {
		L = l; R = r;
		if(l == r){
			left = right = nullptr;
			sum = num[l];
		}else{
			left = new SegTree();
			right = new SegTree();
			int mid = (l + r) / 2;
			left->build(l, mid);
			right->build(mid+1, r);
			sum = left->sum + right->sum;
		}
	}
	void update(int l, int r, LL delta) {
		if(r < L || R < l) return;
		if(l <= L && R <= r){
			acc += delta;
		}else{
			sum += delta * (min(r,R) - max(l,L) + 1);
			left->update(l, r, delta);
			right->update(l, r, delta);

		}
	}
	LL query(int l, int r) {
		if(r < L || R < l) return 0;
		if(acc != 0){
			if(left || right){
				left->acc += acc;
				right->acc += acc;
			}
			sum += acc * (R - L + 1);
			acc = 0;
		}
		if(l <= L && R <= r) return sum;
		return left->query(l,r) + right->query(l,r);
	}
};

int main() {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	for(int i=0; i<n; i++) scanf("%lld", num + i);

	SegTree tree;
	tree.build(0, n-1);

	for(int i=0; i<m+k; i++){
		int a,b,c; LL d;
		scanf("%d", &a);
		if(a == 1){
			// update
			scanf("%d %d %lld", &b, &c, &d);
			b--; c--;
			tree.update(b, c, d);
		}else if(a == 2){
			// query
			scanf("%d %d", &b, &c);
			b--; c--;
			printf("%lld\n", tree.query(b, c));
		}
	}

	return 0;
}
