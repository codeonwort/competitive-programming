// Codeforces Round #379 (Div. 2)
// http://codeforces.com/contest/734

// ID: 734E (Anton and Tree)

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 200000 + 1;
int color[MAX], level[MAX];
bool visited[MAX];
vector<int> G[MAX], H[MAX], rootGroup;

void dfs(int u, int rootV) {
	visited[u] = true;
	for(int i=0; i<G[u].size(); i++){
		int v = G[u][i];
		if(!visited[v]){
			if(color[v] != color[u]){
				rootGroup.push_back(v);
				H[rootV].push_back(v);
				H[v].push_back(rootV);
				dfs(v, v);
			}else{
				dfs(v, rootV);
			}
		}
	}
}

void bfs(int u, int lvl) {
	visited[u] = true;
	level[u] = lvl;
	for(int i=0; i<H[u].size(); i++){
		int v = H[u][i];
		if(!visited[v]){
			bfs(v, lvl + 1);
		}
	}
}

void solve() {
	int n;
	cin >> n;
	for(int i=1; i<=n; i++) scanf("%d", color + i);
	for(int i=0; i<n-1; i++){
		int u, v; scanf("%d %d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}

	memset(visited, 0, sizeof(visited));
	rootGroup.push_back(1);
	dfs(1, 1);

	memset(visited, 0, sizeof(visited));
	bfs(1, 0);
	int end1 = 1;
	for(int i=0; i<rootGroup.size(); i++){
		if(level[rootGroup[i]] > level[end1]){
			end1 = rootGroup[i];
		}
	}
	memset(visited, 0, sizeof(visited));
	bfs(end1, 0);
	int end2 = 1;
	for(int i=0; i<rootGroup.size(); i++){
		if(level[rootGroup[i]] > level[end2]){
			end2 = rootGroup[i];
		}
	}

	int step = (level[end2] + 1) / 2;
	cout << step << endl;
}

int main() {
	solve();
	return 0;
}
