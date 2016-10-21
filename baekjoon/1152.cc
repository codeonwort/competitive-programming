// ID:  1152 (단어의 개수)
// URL: https://www.acmicpc.net/problem/1152

#include <iostream>
using namespace std;

int main() {
	string s;
	getline(cin, s);

	int numWords = 0;
	bool word = false;
	for(int i=0; i<s.size(); i++){
		if(s[i] == ' '){
			word = false;
		}else{
			if(!word) numWords++;
			word = true;
		}
	}

	cout << numWords << endl;

	return 0;
}
