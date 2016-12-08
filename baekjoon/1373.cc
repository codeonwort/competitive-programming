#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	string str;
	vector<int> bin, oct;

	cin >> str;
	reverse(str.begin(), str.end());
	while(str.size() % 3 != 0) str.push_back('0');
	for(auto i=0; i<str.size(); i++){
		bin.push_back(str[i] - '0');
	}

	for(auto i=0; i<bin.size(); i+=3){
		oct.push_back(bin[i+2]*4 + bin[i+1]*2 + bin[i]);
	}
	reverse(oct.begin(), oct.end());

	for(auto i=0; i<oct.size(); i++){
		printf("%d", oct[i]);
	}

	return 0;
}
