// ID:  2902 (KMP는 왜 KMP일까?)
// URL: https://www.acmicpc.net/problem/2902

#include <iostream>
#include <string>
using namespace std;

int main() {
	string s;

	cin >> s;

	cout << s[0];
	for(int i=1; i<s.size()-1; i++){
		if(s[i] == '-') cout << s[i+1];
	}

	return 0;
}
