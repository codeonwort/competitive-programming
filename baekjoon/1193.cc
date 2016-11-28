// ID:  1193 (분수찾기)
// URL: https://www.acmicpc.net/problem/1193

#include <iostream>
#include <vector>
using namespace std;

void solve() {
	long long x;
	cin >> x;

	vector<long long> ys;
	ys.push_back(0);
	long long i = 1;
	while(true){
		int y = i * (i+1) / 2;
		ys.push_back(y);
		if(y > 10000000) break;
		i++;
	}

	i = 1;
	while(ys[i] < x) i++;

	int p = x - ys[i-1]; // p-th number on i-th diagonal
	int row, col;
	if(i % 2 == 0){
		row = p; col = i - (p-1);
	}else{
		col = p; row = i - (p-1);
	}
	cout << row << '/' << col << endl;
}

int main() {
	solve();
	return 0;
}
