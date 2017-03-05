// Codeforces Round #403 (Div. 2)
// C. Andryusha and Colored Balloons
// http://codeforces.com/contest/782/problem/C

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 2 * 100000 + 1;
vector<int> G[MAX];
vector<int> colors(MAX, 0);
int k;

// dfs
void colorize(int v, int color, int parentColor) {
	colors[v] = color;

	int childColor = 0;
	for(int i=0; i<G[v].size(); ++i){
		int u = G[v][i];
		if(colors[u] != 0) continue; // already colored

		childColor += 1;
		while(childColor == color || childColor == parentColor){
			childColor += 1;
		}
		colorize(u, childColor, color);
	}
}

int main() {
	// n = number of vertices
	int n;
	scanf("%d", &n);

	// construct the graph
	for(int i=0; i<n-1; ++i){
		int x, y;
		scanf("%d %d", &x, &y);
		G[x].push_back(y);
		G[y].push_back(x);
	}

	// calculate k
	int v0 = -1; // first vertex to be colored
	k = 0;
	for(int v=1; v<=n; ++v){
		if(G[v].size() > k){
			k = G[v].size();
			v0 = v;
		}
	}
	k += 1; // k = (maximum outdegree in G) + 1

	// colorize the graph
	colorize(v0, 1, 0);

	// output
	printf("%d\n", k);
	for(int v=1; v<=n; ++v){
		printf("%d ", colors[v]);
	}
	puts("");

	return 0;
}
