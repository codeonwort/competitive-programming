// ID:  1922 (네트워크 연결)
// URL: https://www.acmicpc.net/problem/1922

// Category: MST (using Kruskal)

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

struct edge {
	int u, v;
	int weight;
};
bool compareEdge(const edge& e1, const edge& e2) {
	return e1.weight < e2.weight;
}

int parent[1001]; // for union-find
int collapsingFind(int i);
void weightedUnion(int i, int j); // i, j should be roots

int main() {
	int n; // num computers
	int m; // num connections
	vector<edge> edges;

	// input
	scanf("%d", &n);
	scanf("%d", &m);
	int u,v,w;
	edge e;
	for(int i=0; i<m; i++){
		scanf("%d %d %d", &u, &v, &w);
		e.u = u; e.v = v; e.weight = w;
		edges.push_back(e);
	}

	// sort edges by weights
	sort(edges.begin(), edges.end(), compareEdge);

	// init for union-find
	for(int i=1; i<=n; i++) parent[i] = -1;

	// run Kruskal
	vector<edge>::iterator e_ptr = edges.begin();
	long long int cost = 0;
	while(e_ptr != edges.end()){
		edge& e = *e_ptr;
		int r1 = collapsingFind(e.u);
		int r2 = collapsingFind(e.v);
		if(r1 == r2){
			// it makes a cycle. discard
		}else{
			weightedUnion(r1, r2);
			cost += e.weight;
		}
		e_ptr++;
	}

	// output
	printf("%lld\n", cost);

	return 0;
}

int collapsingFind(int i) {
	int root, trail;
	for(root = i; parent[root] >= 0; root = parent[root]){
	}
	for(trail = i; trail != root; trail = parent[trail]){
		parent[trail] = root;
	}
	return root;
}
void weightedUnion(int i, int j) {
	int temp = parent[i] + parent[j];
	if(parent[i] < parent[j]){
		parent[j] = i;
		parent[i] = temp;
	}else{
		parent[i] = j;
		parent[j] = temp;
	}
}
