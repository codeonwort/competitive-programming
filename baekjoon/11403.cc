// ID:  11403 (경로 찾기)
// URL: https://www.acmicpc.net/problem/11403

#include <iostream>
using namespace std;

bool matrix[100][100];

bool dotp(int row, int col, int n) {
	bool b = false;
	for(int i=0; i<n; i++){
		b = b || (matrix[row][i] && matrix[i][col]);
	}
	return b;
}

void square(int n) {
	bool temp[100][100];
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			temp[i][j] = dotp(i, j, n);
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			matrix[i][j] = matrix[i][j] || temp[i][j];
		}
	}
}

int main() {
	int n;

	cin >> n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin >> matrix[i][j];
		}
	}

	for(int i=0; i<n-1; i++){
		square(n);
	}

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout << matrix[i][j] << ' ';
		}
		cout << endl;
	}

	return 0;
}
