// ID:  1717 (집합의 표현)
// URL: https://www.acmicpc.net/problem/1717

// Exercise for union-find of disjoint set

#include <stdio.h>

int parent[1000001];

int collapsingFind(int i) {
	int root, trail, lead;
	for(root = i; parent[root] >= 0; root = parent[root]);
	for(trail = i; trail != root; trail = lead){
		lead = parent[trail];
		parent[trail] = root;
	}
	return root;
}

void weightedUnion(int i, int j) {
	int temp = parent[i] + parent[j];
	if(parent[i] > parent[j]){
		parent[i] = j;
		parent[j] = temp;
	}else{
		parent[j] = i;
		parent[i] = temp;
	}
}

int main() {
	int n; // node: 0 ~ n (total: n+1)
	int m; // num queries

	scanf("%d %d", &n, &m);

	for(int i=0; i<=n; i++){
		parent[i] = -1;
	}

	int q, a, b;
	int rootA, rootB;
	for(int i=0; i<m; i++){
		scanf("%d %d %d", &q, &a, &b);
		if(q == 0){
			// union
			rootA = collapsingFind(a);
			rootB = collapsingFind(b);
			if(rootA >= 0 && rootB >= 0 && rootA == rootB) continue;
			weightedUnion(rootA, rootB);
		}else if(q == 1){
			// find
			if(a == b || collapsingFind(a) == collapsingFind(b)){
				puts("YES");
			}else{
				puts("NO");
			}
		}
	}

	return 0;
}
