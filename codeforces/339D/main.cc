// ID:  339D (Xenia and Bit Operations)
// URL: http://codeforces.com/contest/339/problem/D
// Category: Segment Tree (Single Element Update)
//
#include <stdio.h>

int seg[2 << 18 + 1];

void build(int n) {
	int height = n-1;
	bool isOR = true;
	for(int i = (1<<n)-1; i > 0; i--){
		if(i >> height == 0){
			height--;
			isOR = !isOR;
		}
		if(isOR) seg[i] = seg[i<<1] | seg[i<<1|1];
		else seg[i] = seg[i<<1] ^ seg[i<<1|1];
	}
}

void update(int i, int x, int n) {
	int height = n-1;
	bool isOR = true;
	n = 1 << n;
	seg[n + i] = x;
	for(i = (n+i)/2; i > 0; i = i >> 1){
		if(i >> height == 0){
			height--;
			isOR = !isOR;
		}
		if(isOR) seg[i] = seg[i<<1] | seg[i<<1|1];
		else seg[i] = seg[i<<1] ^ seg[i<<1|1];
	}
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);

	int num = 1 << n;
	for(int i=0; i<num; i++){
		scanf("%d", seg + num + i);
	}
	build(n);

	for(int i=0; i<m; i++){
		int p, b;
		scanf("%d %d", &p, &b);
		p--;
		update(p, b, n);
		printf("%d\n", seg[1]);
	}

	return 0;
}
