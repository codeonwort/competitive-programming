// ID:  1992 (쿼드트리)
// URL: https://www.acmicpc.net/problem/1992

#include <iostream>
#include <string>
using namespace std;

char image[64][64];

string compress(int left, int right, int top, int bottom) {
	if(left == right && top == bottom){
		if(image[top][left] == '0') return "0";
		return "1";
	}
	int midX = (left+right)/2;
	int midY = (top+bottom)/2;
	string topLeft = compress(left, midX, top, midY);
	string topRight = compress(midX+1, right, top, midY);
	string bottomLeft = compress(left, midX, midY+1, bottom);
	string bottomRight = compress(midX+1, right, midY+1, bottom);
	
	bool allZero = topLeft == "0" && topRight == "0"
				&& bottomLeft == "0" && bottomRight == "0";
	bool allOne = topLeft == "1" && topRight == "1"
				&& bottomLeft == "1" && bottomRight == "1";
	if(allZero) return "0";
	if(allOne) return "1";
	return "(" + topLeft + topRight + bottomLeft + bottomRight + ")";
}

int main() {
	int n;

	cin >> n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin >> image[i][j];
		}
	}

	string soln = compress(0, n-1, 0, n-1);
	cout << soln << endl;

	return 0;
}
