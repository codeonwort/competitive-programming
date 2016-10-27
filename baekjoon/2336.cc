// ID: 2336 (굉장한 학생)
// URL: https://www.acmicpc.net/problem/2336
// Category: Segment Tree (RMQ)

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int INF = 1e9;
const int MAX = 500001;

struct Score { int first, second, third; } scores[MAX];
bool compareScore(const Score& a, const Score& b) {
	return a.first < b.first;
}

// segment tree - range minimum query
struct RMQ {
	int start, end;
	RMQ *left, *right;
	int minimum;
	RMQ(int l, int r) {
		start = l; end = r; minimum = INF;
		if(l == r){
			left = right = nullptr;
		}else{
			int mid = (l + r) / 2;
			left = new RMQ(l, mid);
			right = new RMQ(mid+1, r);
		}
	}
	void update(int i, int x) {
		if(start <= i && i <= end){
			if(left || right){
				left->update(i, x);
				right->update(i, x);
				minimum = min(left->minimum, right->minimum);
			}else{
				minimum = x;
			}
		}
	}
	int query(int l, int r) {
		if(r < start || end < l) return INF;
		if(l <= start && end <= r) return minimum;
		return min(left->query(l, r), right->query(l, r));
	}
};

int main() {
	int n;
	scanf("%d", &n);
	for(int i=1; i<=n; i++){
		int x; scanf("%d", &x);
		scores[x-1].first = i;
	}
	for(int i=1; i<=n; i++){
		int x; scanf("%d", &x);
		scores[x-1].second = i;
	}
	for(int i=1; i<=n; i++){
		int x; scanf("%d", &x);
		scores[x-1].third = i;
	}
	sort(scores, scores + n, compareScore);

	int answer = 0;
	RMQ rmq(1, n);
	for(int i=0; i<n; i++){
		int snd = scores[i].second;
		int trd = scores[i].third;
		if(rmq.query(1,snd) > trd) answer += 1;
		rmq.update(snd, trd);
	}

	printf("%d\n", answer);

	return 0;
}
