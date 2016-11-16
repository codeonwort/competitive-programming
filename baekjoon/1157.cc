// ID:  1157 (단어 공부)
// URL: https://www.acmicpc.net/problem/1157

#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

int occurence[26];

int main() {
	string word;
	cin >> word;

	for(int i=0; i<word.size(); i++){
		char ch = word[i];
		if('A' <= ch && ch <= 'Z') ch -= 'A';
		else if('a' <= ch && ch <= 'z') ch -= 'a';
		occurence[ch] += 1;
	}

	int maxCount = 0, maxID = -1;
	for(int i=0; i<26; i++){
		if(occurence[i] > maxCount){
			maxCount = occurence[i];
			maxID = i;
		}
	}

	int maxTypes = 0;
	for(int i=0; i<26; i++){
		if(occurence[i] == maxCount) maxTypes += 1;
	}
	if(maxTypes >= 2){
		cout << "?" << endl;
	}else{
		char ch = 'A' + maxID;
		cout << ch << endl;
	}

	return 0;
}
