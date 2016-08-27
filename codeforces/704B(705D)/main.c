#include <stdio.h>

// ID:	705D (Ant Man)
// URL:	http://codeforces.com/contest/705/problem/D

// This is not an accepted code!
// note: invalid approach. don't use greedy.

int main() {
	int n, s, e;
	int i, j, p;
	long long cost, dx, minCost;
	long long int costAcc=0;
	int minPos;
	long long int xs[5000],as[5000],bs[5000],cs[5000],ds[5000];
	int visited[5000];

	scanf("%d%d%d",&n, &s, &e);
	for(i=0; i<n; i++) scanf("%I64d",xs+i);
	for(i=0; i<n; i++) scanf("%I64d",as+i);
	for(i=0; i<n; i++) scanf("%I64d",bs+i);
	for(i=0; i<n; i++) scanf("%I64d",cs+i);
	for(i=0; i<n; i++) scanf("%I64d",ds+i);
	for(i=0; i<n; i++) visited[i] = 0;

	// start from s
	s -= 1; e -= 1;
	p = s;
	visited[p] = 1;
	for(i=0; i<n-2; i++){
		// find next position with minimum cost
		minPos = -1;
		minCost = 40000000001L;
		// case: left jump
		for(j=0; j<p; j++){
			if(visited[j] || j == e) continue;
			dx = xs[p] - xs[j];
			cost = dx + cs[p] + bs[j];
			if(cost < minCost){
				minCost = cost; minPos = j;
			}
		}
		// case : right jump
		for(j=p+1; j<n; j++){
			if(visited[j] || j == e) continue;
			dx = xs[j] - xs[p];
			cost = dx + ds[p] + as[j];
			if(cost < minCost){
				minCost = cost; minPos = j;
			}
		}
		// do jump
		visited[minPos] = 1;
		costAcc += minCost;
		p = minPos;
	}
	
	// end on e
	if(p < e) costAcc += (xs[e]-xs[p]) + ds[p] + as[e];
	else costAcc += (xs[p]-xs[e]) + cs[p] + bs[e];

	printf("%I64d\n", costAcc);

	return 0;
}
