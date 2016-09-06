// ID:  1780 (종이의 개수)
// URL: https://www.acmicpc.net/problem/1780

#include <iostream>
#include <vector>
using namespace std;

int table[3000][3000]; // 3^7 = 81 * 27 ~= 2400
int numNeg, numZero, numPos;

int recurse(int left, int right, int top, int bottom);

int main() {
	int n;

	// input
	cin >> n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin >> table[i][j];
		}
	}

	// solve
	numNeg = numZero = numPos = 0;
	recurse(0, n-1, 0, n-1);

	cout << numNeg << endl;
	cout << numZero << endl;
	cout << numPos << endl;

	return 0;
}

int recurse(int left, int right, int top, int bottom) {
	if(left == right && top == bottom){
		return table[top][left];
	}

	int spaceX = (right - left + 1) / 3;
	int spaceY = (bottom - top + 1) / 3;

	vector<int> sub;
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			int y0 = top + i * spaceY;
			int x0 = left + j * spaceX;
			sub.push_back(recurse(x0,x0+spaceX-1, y0,y0+spaceY-1));
		}
	}

	// all slices are -1
	bool ok = true;
	for(int i=0; i<9; i++){
		if(sub[i] != -1){ ok = false; break; }
	}
	if(ok) return -1;

	// all slices are 0
	ok = true;
	for(int i=0; i<9; i++){
		if(sub[i] != 0){ ok = false; break; }
	}
	if(ok) return 0;

	// all slices are 1
	ok = true;
	for(int i=0; i<9; i++){
		if(sub[i] != 1){ ok = false; break; }
	}
	if(ok) return 1;

	// otherwise
	for(int i=0; i<9; i++){
		if(sub[i] == -1) numNeg++;
		else if(sub[i] == 0) numZero++;
		else if(sub[i] == 1) numPos++;
		else { /* do nothing */ }
	}
	return 123;
}
