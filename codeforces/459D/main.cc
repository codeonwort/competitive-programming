// ID: 459D (Pashmak and Parmida's problem)
// URL: http://codeforces.com/contest/459/problem/D
// Category: Fenwick Tree

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int MAX = 1000000 + 1;
int ary[MAX], temp[MAX];
int BIT[MAX], n;
int L[MAX], R[MAX], cnt[MAX];

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

	// map values of ary[1..n] into [1..n]
	for(int i=0; i<n; i++) temp[i] = ary[i];
	sort(temp, temp + n);
	int p = 0;
	for(int i=0; i<n; i++){
		if(i > 0 && temp[i] == temp[i-1]) continue;
		temp[p++] = temp[i];
	}
	for(int i=0; i<n; i++){
		ary[i] = (lower_bound(temp, temp + p, ary[i]) - temp) + 1;
	}

	// calculate L[i] and R[i]
	memset(cnt, 0, sizeof(cnt));
	for(int i=1; i<=n; i++){
		int x = ary[i-1];
		cnt[x]++;
		L[i] = cnt[x];
	}
	memset(cnt, 0, sizeof(cnt));
	for(int i=n; i>=1; i--){
		int y = ary[i-1];
		cnt[y]++;
		R[i] = cnt[y];
	}

	// number of pairs (i, j) s.t. i < j and L[i] > R[j]
	memset(BIT, 0, sizeof(BIT));
	long long answer = 0;
	for(int i=1; i<=n; i++){
		answer += query(n) - query(R[i]);
		update(L[i], 1);
	}

	// output
	printf("%lld\n", answer);

	return 0;
}
