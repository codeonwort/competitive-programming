// ID:  714B (Filya and Homework)
// URL: a

//#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	int n, x;
	vector<int> xs;

	cin >> n;
	for(int i=0; i<n; i++){
		cin >> x;
		if(find(xs.begin(), xs.end(), x) == xs.end()){
			xs.push_back(x);
		}
		if(xs.size() >= 4){
			cout << "NO" << endl;
			return 0;
		}
	}
	sort(xs.begin(), xs.end());

	if(xs.size() == 1){
		cout << "YES" << endl;
		return 0;
	}

	for(int i=1; i<xs.size(); i++){
		if(xs[i] - xs[i-1] != xs[1] - xs[0]){
			cout << "NO" << endl;
			return 0;
		}
	}

	cout << "YES" << endl;

	return 0;
}
