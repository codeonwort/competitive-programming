// ID:  11047 (동전 0)
// URL: https://www.acmicpc.net/problem/11047

#include <iostream>
using namespace std;

int main() {
	int n, k;
	int value[10];

	cin >> n >> k;
	for(int i=0; i<n; i++) cin >> value[i];

	int cnt = 0;
	int i = n-1;
	while(k != 0){
		if(k >= value[i]){
			cnt += k / value[i];
			k = k % value[i];
		}
		i--;
	}

	cout << cnt << endl;

	return 0;
}
