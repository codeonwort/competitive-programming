// ID:  2188 (축사 배정)
// URL: https://www.acmicpc.net/problem/2188
// Category: Flow Network

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 402;
int capacity[MAX][MAX];
int flow[MAX][MAX];

int network_flow(int source, int sink, int n) {
	int maxFlow = 0;

	while(true){
		vector<int> parent(n, -1);
		parent[source] = source;
		queue<int> q;
		q.push(source);

		// find aug path
		while(!q.empty() && parent[sink] == -1){
			int u = q.front(); q.pop();
			for(int v=0; v<n; v++){
				if(capacity[u][v] - flow[u][v] > 0 && parent[v] == -1){
					q.push(v);
					parent[v] = u;
				}
			}
		}

		// no more aug path -> stop
		if(parent[sink] == -1) break;

		// increase flow
		int aug = 987654321;
		for(int p = sink; p != source; p = parent[p]){
			int from = parent[p], to = p;
			aug = min(aug, capacity[from][to] - flow[from][to]);
		}
		for(int p = sink; p != source; p = parent[p]){
			int from = parent[p], to = p;
			flow[from][to] += aug;
			flow[to][from] -= aug;
		}
		maxFlow += aug;
	}

	return maxFlow;
}

int main() {
	// num cows, num jails
	int n, m;
	cin >> n >> m;

	// init capacity and flow
	for(int i=0; i<MAX; i++){
		for(int j=0; j<MAX; j++){
			capacity[i][j] = flow[i][j] = 0;
		}
	}

	// cow:  1 ~ N
	// jail: N+1 ~ N+M
	for(int i=1; i<=n; i++){
		int numWanted;
		cin >> numWanted;
		for(int j=0; j<numWanted; j++){
			int want;
			cin >> want;
			capacity[i][n + want] = 1;
		}
	}
	// source to all cows, all jails to sink
	for(int i=1; i<=n; i++) capacity[0][i] = 1;
	for(int i=n+1; i<=n+m; i++) capacity[i][n+m+1] = 1;
	int maxFlow = network_flow(0, n+m+1, n+m+2);

	cout << maxFlow << endl;

	return 0;
}
