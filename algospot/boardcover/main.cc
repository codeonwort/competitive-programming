// ID:  BOARDCOVER
// URL: https://algospot.com/judge/problem/read/BOARDCOVER

#include <iostream>

using namespace std;

int coverType[4][3][2] = {
	{ {0,0}, {1,0}, {0,1} },
	{ {0,0}, {0,1}, {1,1} },
	{ {0,0}, {1,0}, {1,1} },
	{ {0,0}, {1,0}, {1,-1} }
};
int board[20][20];
void solve();
bool set(int y, int x, int h, int w, int type, int delta);
int recurse(int h, int w);

int main() {
	int t;
	cin >> t;
	while(t --> 0) solve();
	return 0;
}

void solve() {
	int w,h;
	int whites = 0;

	// input
	char block;
	cin >> h >> w;
	for(int i=0; i<h; i++){
		for(int j=0; j<w; j++){
			cin >> block;
			if(block == '#') board[i][j] = 1;
			else { board[i][j] = 0; whites++; }
		}
	}

	// debug
	/*for(int i=0; i<h; i++){
		for(int j=0; j<w; j++){
			cout << board[i][j];
		}
		cout << endl;
	}*/

	// special case
	if(whites % 3 != 0){
		cout << 0 << endl;
		return;
	}

	int n = whites / 3; // num of blocks
	int soln = recurse(h, w);
	cout << soln << endl;
}

bool set(int y, int x, int h, int w, int type, int delta) {
	bool ok = true;
	for(int i=0; i<3; i++){
		int ny = y + coverType[type][i][0];
		int nx = x + coverType[type][i][1];
		if(ny < 0 || ny >= h || nx < 0 || nx >= w) ok = false;
		else if((board[ny][nx] += delta) > 1) ok = false;
	}
	return ok;
}

int recurse(int h, int w) {
	// location to place first block
	int y = -1, x = -1;
	for(int i=0; i<h; i++){
		for(int j=0; j<w; j++){
			if(board[i][j] == 0){
				y = i; x = j; break;
			}
		}
		if(y != -1) break;
	}

	// base case: solution found
	if(y == -1) return 1;

	int soln = 0;
	for(int type=0; type<4; type++){
		if(set(y, x, h, w, type, 1)){
			soln += recurse(h, w);
		}
		set(y, x, h, w, type, -1);
	}
	return soln;
}

