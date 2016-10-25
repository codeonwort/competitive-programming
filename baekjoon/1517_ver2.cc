// ID:  1517 (버블소트)
// URL: https://www.acmicpc.net/problem/1517
// Category: Fenwick Tree, Segment Tree

// Third trial (Fenwick Tree)
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int MAX = 500001;
int ary[MAX], temp[MAX];
int BIT[MAX], n;

int query(int i) {
	int answer = 0;
	while(i > 0){
		answer += BIT[i];
		i -= i & -i;
	}
	return answer;
}

void update(int i, int delta) {
	while(i <= n){
		BIT[i] += delta;
		i += i & -i;
	}
}

int main() {
	// input
	scanf("%d", &n);
	for(int i=0; i<n; i++) scanf("%d", ary + i);

	// map input values into [1:500000]
	for(int i=0; i<n; i++) temp[i] = ary[i];
	sort(temp, temp + n);
	int p = 0;
	for(int i=0; i<n; i++){
		if(i > 0 && temp[i] == temp[i-1]) continue;
		temp[p++] = temp[i];
	}

	// solve
	memset(BIT, 0, sizeof(BIT));
	long long answer = 0;
	for(int i=0; i<n; i++){
		int x = (lower_bound(temp, temp + p, ary[i]) - temp) + 1;
		answer += query(n) - query(x);
		update(x, 1);
	}

	// output
	printf("%lld\n", answer);

	return 0;
}

/* Second trial
// This code cannot be accepted due to MLE
// Memory limit: 8MB
// Memory usage: three arrays use 7.62MB

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int MAX = 500001;
int ary[MAX], temp[MAX];
int tree[MAX * 2];

int query(int l, int r, int node, int start, int end) {
	if(r < start || end < l) return 0;
	if(l <= start && end <= r) return tree[node];
	int mid = (start + end) / 2;
	return query(l, r, node*2, start, mid) + query(l, r, node*2+1, mid+1, end);
}

void update(int ix, int delta, int node, int start, int end) {
	if(start <= ix && ix <= end){
		tree[node] += delta;
		if(start != end){
			int mid = (start + end) / 2;
			update(ix, delta, node*2, start, mid);
			update(ix, delta, node*2+1, mid+1, end);
		}
	}
}

int main() {
	// input
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++) scanf("%d", ary + i);

	// map input values into [1:500000]
	for(int i=0; i<n; i++) temp[i] = ary[i];
	sort(temp, temp + n);
	int p = 0;
	for(int i=0; i<n; i++){
		if(i > 0 && temp[i] == temp[i-1]) continue;
		temp[p++] = temp[i];
	}

	// solve
	memset(tree, 0, sizeof(tree));
	int answer = 0;
	for(int i=0; i<n; i++){
		int x = (lower_bound(temp, temp + p, ary[i]) - temp) + 1;
		if(x != n) answer += query(x+1, n, 1,1,n);
		update(x, 1, 1,1,n);
	}

	// output
	printf("%d\n", answer);

	return 0;
}*/

/* First trial
// This code cannot be accepted due to MLE
// Memory limit: 8MB
// Memory usage: Segment tree itself uses 19MB (1 million nodes * 20 bytes per node)

#include <stdio.h>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;

const int MAX = 500000;
int ary[MAX], temp[MAX];

struct SegTree {
	int start, end, sum;
	SegTree *left, *right;
	SegTree(int s, int e) {
		if(s == e){
			left = right = nullptr;
		}else{
			int mid = (s + e) / 2;
			left = new SegTree(s, mid);
			right = new SegTree(mid+1, e);
		}
		start = s; end = e; sum = 0;
	}
	int query(int l, int r) {
		if(r < start || end < l) return 0;
		else if(l <= start && end <= r) return sum;
		return left->query(l, r) + right->query(l, r);
	}
	void update(int ix, int delta) {
		if(start <= ix && ix <= end){
			sum += delta;
			if(left || right){
				left->update(ix, delta);
				right->update(ix, delta);
			}
		}
	}
};

int main() {
	int n;

	// input
	scanf("%d", &n);
	for(int i=0; i<n; i++) scanf("%d", ary + i);

	// map input values into [0:500000)
	for(int i=0; i<n; i++) temp[i] = ary[i];
	sort(temp, temp + n);
	int x = 0;
	map<int, int> mapping;
	for(int i=0; i<n; i++){
		if(i > 0 && temp[i] != temp[i-1]) x++;
		mapping[temp[i]] = x;
	}

	// solve
	int answer = 0;
	SegTree tree(0, n-1);
	for(int i=0; i<n; i++){
		int x = mapping[ary[i]];
		if(x != n-1) answer += tree.query(x+1, n-1);
		tree.update(x, 1);
	}

	// output
	printf("%d\n", answer);

	return 0;
}
*/
