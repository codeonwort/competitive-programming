// ID:  723E (One-Way Reform)
// URL: http://codeforces.com/problemset/problem/723/E
// Category: Euler circuit, Euler path

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// adj[i][j]: number of roads from i to j
int adj[200][200];
bool connected[200][200];
bool visited[200];

void eulerCircuit(int u, int n, vector<int>& circuit) {
	visited[u] = true;
	for(int v=0; v<n; v++){
		if(adj[u][v] > 0){
			adj[u][v] -= 1;
			adj[v][u] -= 1;
			eulerCircuit(v, n, circuit);
		}
	}
	circuit.push_back(u);
}

void solve() {
	int n; // num cities
	int m; // num roads
	cin >> n >> m;

	// init
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			adj[i][j] = 0;
			connected[i][j] = false;
		}
		visited[i] = false;
	}

	// input
	for(int i=0; i<m; i++){
		int u, v;
		cin >> u >> v;
		u--; v--;
		adj[u][v] += 1;
		adj[v][u] += 1;
		connected[u][v] = connected[v][u] = true;
	}

	// collect cities whose number of connected roads is odd
	vector<int> odds;
	for(int i=0; i<n; i++){
		int numRoads = 0;
		for(int j=0; j<n; j++) if(connected[i][j]) numRoads++;
		if(numRoads % 2 == 1) odds.push_back(i);
	}
	int numEvens = n - odds.size();

	// augment the graph
	for(int i=0; i<odds.size(); i+=2){
		int u = odds[i], v = odds[i+1];
		adj[u][v] += 1;
		adj[v][u] += 1;
	}

	// output 1
	cout << numEvens << endl;

	// find euler circuits and print them
	for(int i=0; i<n; i++){
		if(visited[i]) continue;
		vector<int> circuit;
		eulerCircuit(i, n, circuit);
		for(int j=0; j<circuit.size()-1; j++){
			int u = circuit[j];
			int v = circuit[j+1];
			if(connected[u][v]){
				cout << (u+1) << ' ' << (v+1) << endl;
				connected[u][v] = connected[v][u] = false;
			}
		}
	}
}

int main() {
	int tests;
	cin >> tests;
	while(tests --> 0) solve();
	return 0;
}
