// ID:  716B (Complete the Word)
// URL: http://codeforces.com/problemset/problem/716/B

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

bool found = false; // is there any solution?

void recurse(string& s, int begin, int end); // divide
bool check(string& s, int begin); // conquer

int main() {
	string str;

	cin >> str;

	// find an adequate substring. if any, fill it
	recurse(str, 0, str.size());
	
	if(found){
		// fill remaining ?s
		for(int i=0; i<str.size(); i++){
			if(str[i] == '?') str[i] = 'A';
		}
		cout << str << endl;
	}
	else cout << -1 << endl;

	return 0;
}

void recurse(string& s, int begin, int end) {
	if(found || end - begin < 26) return;

	int mid = (begin + end) / 2;
	for(int i = max(0,mid-26); i <= mid; i++){
		// check s[i:i+26)
		if(i + 25 >= s.size()) break;
		if(check(s, i)){
			return;
		}
	}

	recurse(s, begin, mid);
	recurse(s, mid, end);
}

bool check(string& s, int begin) {
	if(begin < 0 || begin + 25 >= s.size()) return false;

	// true if each letter appears in s[begin:begin+26)
	bool filled[26];
	for(int j = 0; j < 26; j++) filled[j] = false;

	// test s[begin:begin+26)
	for(int j = 0; j < 26; j++){
		char ch = s[begin + j];
		if(ch != '?' && filled[ch - 'A']){
			return false;
		}else if(ch != '?'){
			filled[ch - 'A'] = true;
		}
	}

	// a proper substring has been found. fill it
	found = true;
	vector<char> rest;
	for(int j = 0; j < 26; j++){
		if(!filled[j]){
			rest.push_back('A' + j);
		}
	}
	int k = 0;
	for(int j = 0; j < 26; j++){
		if(s[begin+j] == '?'){
			s[begin+j] = rest[k];
			k++;
		}
	}

	return true;
}
