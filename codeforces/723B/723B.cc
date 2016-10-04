// ID:  723B (Text Document Analysis)
// URL: http://codeforces.com/problemset/problem/723/B

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

bool isLetter(char ch) {
	return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z');
}
bool isSep(char ch) {
	return ch == '_' || ch == '(' || ch == ')';
}

int main() {
	int n;
	string str;
	cin >> n >> str;
	str = "_" + str + "_";

	vector<string> outWords;
	vector<string> inWords;
	bool isWord = false;
	bool insideParen = false;
	int wordBegin;
	for(int i=0; i<str.size(); i++){
		char ch = str[i];

		if(isLetter(ch)){
			if(!isWord){
				isWord = true;
				wordBegin = i;
			}
		}else{
			if(isWord){
				// end of a word
				isWord = false;
				if(!insideParen){
					outWords.push_back(str.substr(wordBegin, i - wordBegin));
				}else{
					inWords.push_back(str.substr(wordBegin, i - wordBegin));
				}
			}
		}

		if(ch == '(') insideParen = true;
		else if(ch == ')') insideParen = false;
	}

	int maxLen = 0, inner = inWords.size();
	for(int i=0; i<outWords.size(); i++){
		int len = outWords[i].size();
		maxLen = max(maxLen, len);
	}
	cout << maxLen << ' ' << inner << endl;

	return 0;
}
