// ID:	PICNIC
// URL:	https://algospot.com/judge/problem/read/PICNIC

#include <iostream>

using namespace std;

bool isFriend[10][10];
bool visited[10];

void solve();
int count(int num);

int main() {
	int t;
	cin >> t;
	while(t --> 0) solve();

	return 0;
}

void solve() {
	int n,m;

	// init
	for(int i=0; i<10; i++){
		for(int j=0; j<10; j++){
			isFriend[i][j] = false;
		}
		visited[i] = false;
	}

	// input
	cin >> n >> m;
	for(int i=0; i<m; i++){
		int x, y;
		cin >> x >> y;
		isFriend[x][y] = true;
		isFriend[y][x] = true;
	}

	// solve
	int soln = count(n);
	cout << soln << endl;
}

int count(int n) {
	int free = -1;
	for(int i=0; i<n; i++){
		if(visited[i] == false){
			free = i; break;
		}
	}
	if(free == -1) return 1;

	int soln = 0;
	visited[free] = true;
	for(int j=free+1; j<n; j++){
		if(visited[j] || (!isFriend[free][j])) continue;
		visited[j] = true;
		soln += count(n);
		visited[j] = false;
	}
	visited[free] = false;

	return soln;
}

