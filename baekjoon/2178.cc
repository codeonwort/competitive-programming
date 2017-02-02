// ID:  2178 (미로 탐색)
// URL: https://www.acmicpc.net/problem/2178

#include <iostream>
#include <utility>
#include <queue>
using namespace std;

const int MAX = 101;
using Point = pair<int,int>;

char board[MAX][MAX];
bool visited[MAX][MAX];
int n, m;

void solve() {
	// input
	cin >> n >> m;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			cin >> board[i][j];
			visited[i][j] = false;
		}
	}

	// solve
	queue<Point> Q;
	int step = 1;

	Q.push(Point(0,0));
	visited[0][0] = true;
	auto add = [&](int y, int x) {
		if(x < 0 || x >= m || y < 0 || y >= n) return;
		if(visited[y][x] == false && board[y][x] == '1'){
			Q.push(Point(y,x));
			visited[y][x] = true;
		}
	};
	bool stop;
	while(!Q.empty()){
		stop = false;
		int size = Q.size();
		while(size --> 0){
			Point pt = Q.front(); Q.pop();
			int y = pt.first, x = pt.second;
			if(x == m - 1 && y == n - 1){
				stop = true; break;
			}else{
				add(y-1,x);
				add(y+1,x);
				add(y,x-1);
				add(y,x+1);
			}
		}
		if(stop) break;
		++step;
	}

	// output
	cout << step << endl;
}

int main() {
	solve();
	return 0;
}
