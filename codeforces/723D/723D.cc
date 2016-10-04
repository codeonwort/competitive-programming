// ID:  723D (Lakes in Berland)
// URL: http://codeforces.com/problemset/problem/723/D

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool visited[50][50];
int map[50][50];

int n, m;	// size of the land
int k;		// make the land contains 'k' lakes

struct Lake {
	int y, x, area, id;
};
bool compareLake(const Lake& a, const Lake& b) {
	return a.area < b.area;
}

int floodFill(int y, int x, int prev, int value) {
	if(y < 0 || y >= n || x < 0 || x >= m) return 0;
	if(visited[y][x] || map[y][x] == 0) return 0;
	visited[y][x] = true;
	if(map[y][x] == prev){
		map[y][x] = value;
		return 1 + floodFill(y-1, x, prev, value)
				+ floodFill(y, x-1, prev, value)
				+ floodFill(y, x+1, prev, value) 
				+ floodFill(y+1, x, prev, value);
	}
}

int main() {
	cin >> n >> m >> k;

	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			char ch;
			cin >> ch;
			if(ch == '*') map[i][j] = 0; // wall
			else if(ch == '.') map[i][j] = 1; // water
		}
	}

	// temporarily convert all waters touching the ocean into walls
	for(int i=0; i<n; i++){
		floodFill(i, 0, 1, -1);
		floodFill(i, m-1, 1, -1);
	}
	for(int j=0; j<m; j++){
		floodFill(0, j, 1, -1);
		floodFill(n-1, j, 1, -1);
	}

	// find lakes
	vector<Lake> lakes;
	int lakeId = 2;
	for(int i=1; i<n-1; i++){
		for(int j=1; j<m-1; j++){
			if(map[i][j] == 1){
				Lake lake;
				lake.y = i; lake.x = j;
				lake.area = floodFill(i, j, 1, lakeId);
				lake.id = lakeId;
				lakeId++;
				lakes.push_back(lake);
			}
		}
	}
	sort(lakes.begin(), lakes.end(), compareLake);

	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			visited[i][j] = false;
		}
	}

	int changes = 0;
	int need = lakes.size() - k; // # of lakes to eliminate
	for(int i=0; i<need; i++){
		Lake& L = lakes[i];
		changes += L.area;
		floodFill(L.y, L.x, L.id, 0);
	}

	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(map[i][j] == -1 || map[i][j] > 1) map[i][j] = 1;
		}
	}

	// output
	cout << changes << endl;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(map[i][j] == 0) cout << '*';
			else cout << '.';
		}
		cout << endl;
	}

	return 0;
}
