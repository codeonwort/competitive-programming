// ID:  1707 (이분 그래프)
// URL: https://www.acmicpc.net/problem/1707
// Category: Bipartite Graph

#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

const int MAX = 20000;
vector<int> G[MAX];
bool visited[MAX];
bool isWhite[MAX];
bool impossible;

void dfs(int u, bool white) {
	visited[u] = true;
	isWhite[u] = white;
	for(int i=0; i<G[u].size(); i++){
		int v = G[u][i];
		if(!visited[v]){
			dfs(v, !white);
		}else if(isWhite[u] == isWhite[v]){
			impossible = true; break;
		}
	}
}

void solve() {
	int numVertices, numEdges;
	scanf("%d %d", &numVertices, &numEdges);

	for(int i=0; i<MAX; i++) G[i].clear();
	for(int i=0; i<numEdges; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		u--; v--;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	memset(visited, false, sizeof(visited));
	memset(isWhite, false, sizeof(isWhite));
	impossible = false;

	for(int i=0; i<numVertices; i++){
		if(!visited[i]) dfs(i, true);
		if(impossible) break;
	}

	puts(impossible ? "NO" : "YES");
}

int main() {
	int tests;
	scanf("%d", &tests);
	while(tests --> 0) solve();
	return 0;
}
