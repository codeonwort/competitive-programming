// ID:  11404 (플로이드)
// URL: https://www.acmicpc.net/problem/11404

#include <iostream>
using namespace std;

// cost[k][i][j]: min. cost from i to j passing by first k cities
int weight[100][100];
int cost[101][100][100];

int main() {
	int n, m;

	// input
	cin >> n >> m;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			weight[i][j] = i == j ? 0 : 1e6;
		}
	}
	for(int i=0; i<m; i++){
		int u, v, w;
		cin >> u >> v >> w;
		u--; v--;
		weight[u][v] = min(weight[u][v], w);
	}

	// floyd-warshall
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cost[0][i][j] = weight[i][j];
			for(int k=1; k<=n; k++){
				cost[k][i][j] = 1e8;
			}
		}
	}
	for(int k=1; k<=n; k++){
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				cost[k][i][j] = min(cost[k-1][i][j], cost[k-1][i][k-1] + cost[k-1][k-1][j]);
			}
		}
	}

	// output
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			// minimum cost of i -> j
			int x = cost[n][i][j];
			if(x == 1e8) x = 0;
			cout << x << ' ';
		}
		cout << endl;
	}

	return 0;
}
