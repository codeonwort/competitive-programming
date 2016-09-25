// ID:  2606 (바이러스)
// URL: https://www.acmicpc.net/problem/2606

#include <iostream>
using namespace std;

bool conn[100][100];
bool visited[100];

void dfs(int v, int n) {
	visited[v] = true;
	for(int i=0; i<n; i++){
		if(conn[v][i] && !visited[i]){
			dfs(i, n);
		}
	}
}

int main() {
	int n, m;

	cin >> n >> m;
	for(int i=0; i<100; i++){
		for(int j=0; j<100; j++){
			conn[i][j] = false;
		}
		visited[i] = false;
	}
	for(int i=0; i<m; i++){
		int u, v;
		cin >> u >> v;
		u--; v--;
		conn[u][v] = conn[v][u] = true;
	}

	dfs(0, n);

	int cnt = 0;
	for(int i=1; i<n; i++){
		if(visited[i]) cnt++;
	}
	cout << cnt << endl;

	return 0;
}
