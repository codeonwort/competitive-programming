// ID:  5419 (북서풍)
// URL: https://www.acmicpc.net/problem/5419
// Category: Fenwick Tree

#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 75001;
int xs[MAX], ys[MAX];

struct Point { int x, y; } points[MAX];
bool comparePoint(const Point& a, const Point& b) {
	if(a.x == b.x) return a.y < b.y;
	return a.x > b.x;
}

int temp[MAX];
void compact(int xs[], int n) {
	for(int i=0; i<n; i++) temp[i] = xs[i];
	sort(temp, temp + n);
	int p = 0;
	for(int i=0; i<n; i++){
		if(i > 0 && temp[i] == temp[i-1]) continue;
		temp[p++] = temp[i];
	}
	for(int i=0; i<n; i++){
		xs[i] = lower_bound(temp, temp + p, xs[i]) - temp + 1;
	}
}

struct BIT {
	int n;
	int sum[MAX];
	BIT(int size) {
		n = size;
		memset(sum, 0, sizeof(sum));
	}
	int query(int i) {
		int a = 0;
		while(i > 0){
			a += sum[i];
			i -= i & -i;
		}
		return a;
	}
	void update(int i, int x) {
		while(i <= n){
			sum[i] += x;
			i += i & -i;
		}
	}
};

void solve() {
	// input
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++) scanf("%d %d", xs + i, ys + i);

	// preprocess
	compact(xs, n);
	compact(ys, n);
	for(int i=0; i<n; i++){
		points[i].x = xs[i];
		points[i].y = ys[i];
	}
	sort(points, points + n, comparePoint);

	// solve
	long long answer = 0;
	BIT tree(n);
	for(int i=0; i<n; i++){
		answer += tree.query(points[i].y);
		tree.update(points[i].y, 1);
	}
	printf("%lld\n", answer);
}

int main() {
	int t;
	scanf("%d", &t);
	while(t --> 0) solve();
	return 0;
}
