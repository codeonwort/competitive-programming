// ID:  11399 (ATM)
// URL: https://www.acmicpc.net/problem/11399

#include <algorithm>
#include <iostream>
using namespace std;

int main() {
	int n;
	int time[1000];

	cin >> n;
	for(int i=0; i<n; i++) cin >> time[i];

	sort(time, time+n);

	int wait = 0;
	int total = 0;
	for(int i=0; i<n; i++){
		total += wait + time[i];
		wait += time[i];
	}

	cout << total << endl;

	return 0;
}
