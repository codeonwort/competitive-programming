// ID:  3780 (Corporative Network)
// URL: https://www.acmicpc.net/problem/3780

#include <stdio.h>
#include <algorithm>
using namespace std;

int root[20001], parent[20001], cost[20001];

int findRoot(int i) {
	int R, trail;
	for(R = i; root[R] >= 0; R = root[R]);
	for(trail = i; trail != R; trail = root[trail]){
		root[trail] = R;
	}
	return R;
}
void unionToRight(int i, int j) {
	// i is gauranteed to be a root of a set
	// j is not
	if(parent[i] == -1){
		cost[i] = abs(i - j) % 1000;
	}
	int rootJ = findRoot(j);
	parent[i] = j;
	root[i] = rootJ;
}
void updateCost(int i) {
	if(parent[i] == -1 || root[i] == -1) return;
	findRoot(i);
	if(root[i] != parent[i]){
		updateCost(parent[i]);
		cost[i] += cost[parent[i]];
		parent[i] = root[i];
	}
}

void solve() {
	int n; // num enterprises

	scanf("%d", &n);
	for(int i=1; i<=n; i++){
		parent[i] = -1;
		root[i] = -1;
		cost[i] = 0;
	}

	char cmd;
	int i,j;
	while(1){
		scanf("%c", &cmd);
		if(cmd == 'E'){
			scanf("%d", &i);
			updateCost(i);
			printf("%d\n", cost[i]);
		}else if(cmd == 'I'){
			scanf("%d %d", &i, &j);
			unionToRight(i, j);
		}else if(cmd == 'O') break;
	}
}

int main() {
	int t;
	scanf("%d", &t);
	while(t --> 0) solve();
	return 0;
}
