// ID:  719A (Vitya in the Countryside)
// URL: http://codeforces.com/contest/719/problem/A

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
	int n;
	vector<int> xs;

	cin >> n;
	for(int i=0; i<n; i++){
		int x;
		cin >> x;
		xs.push_back(x);
	}

	string answer;
	if(n == 1){
		if(xs[0] == 0) answer = "UP";
		else if(xs[0] == 15) answer = "DOWN";
		else answer = "-1";
	}else{
		int last = xs[n-1];
		int before = xs[n-2];
		if(before < last){
			if(last == 15) answer = "DOWN";
			else answer = "UP";
		}else if(before > last){
			if(before == 1 && last == 0) answer = "UP";
			else answer = "DOWN";
		}
	}

	cout << answer << endl;

	return 0;
}
