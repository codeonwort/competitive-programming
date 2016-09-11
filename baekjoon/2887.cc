// ID:  2877 (행성 터널)
// URL: https://www.acmicpc.net/problem/2877

// Category: MST (using Kruskal)
// Note: Exactly same problem with 1922

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

struct vertex { int x, y, z, id; };
bool compX(const vertex& v1, const vertex& v2) { return v1.x < v2.x; }
bool compY(const vertex& v1, const vertex& v2) { return v1.y < v2.y; }
bool compZ(const vertex& v1, const vertex& v2) { return v1.z < v2.z; }

struct edge {
	int u, v;
	int weight;
};
bool compareEdge(const edge& e1, const edge& e2) {
	return e1.weight < e2.weight;
}

int parent[1000000]; // for union-find
int collapsingFind(int i);
void weightedUnion(int i, int j); // i, j should be roots

int main() {
	int n; // num planets
	int m; // num connections
	vector<edge> edges;
	vector<vertex> vertices;

	// input
	scanf("%d", &n);
	vertex v;
	for(int i=0; i<n; i++){
		v.id = i;
		scanf("%d %d %d", &v.x, &v.y, &v.z);
		vertices.push_back(v);
	}

	// sort vertices by x
	sort(vertices.begin(), vertices.end(), compX);
	for(int i=0; i<n-1; i++){
		edge e;
		e.u = vertices[i].id; e.v = vertices[i+1].id;
		e.weight = vertices[i+1].x - vertices[i].x;
		edges.push_back(e);
	}
	// sort vertices by y
	sort(vertices.begin(), vertices.end(), compY);
	for(int i=0; i<n-1; i++){
		edge e;
		e.u = vertices[i].id; e.v = vertices[i+1].id;
		e.weight = vertices[i+1].y - vertices[i].y;
		edges.push_back(e);
	}
	// sort vertices by z
	sort(vertices.begin(), vertices.end(), compZ);
	for(int i=0; i<n-1; i++){
		edge e;
		e.u = vertices[i].id; e.v = vertices[i+1].id;
		e.weight = vertices[i+1].z - vertices[i].z;
		edges.push_back(e);
	}

	// sort edges by weights
	sort(edges.begin(), edges.end(), compareEdge);

	// init for union-find
	for(int i=0; i<n; i++) parent[i] = -1;

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
