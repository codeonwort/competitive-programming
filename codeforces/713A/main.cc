// ID:  714C (Sonya and Queries)
// URL: a

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <utility>
using namespace std;

#define LL long long

void modify(map<string,int>& dict, string& pat, int delta) {
	if(dict.find(pat) == dict.end()){
		dict.insert(make_pair(pat, delta));
	}else{
		dict.find(pat)->second += delta;
	}
}

int main() {
	int t;
	char cmd; string str,pat;
	map<string,int> dict;

	cin >> t;
	while(t --> 0){
		cin >> cmd >> str;
		if(cmd == '+' || cmd == '-'){
			int delta = (cmd == '+') ? 1 : -1;
			int n = str.size();
			pat = str;
			for(int i=0; i<pat.size(); i++){
				pat[i] = ((pat[i] - '0') & 1) ? '1' : '0';
			}
			modify(dict, pat, delta);
		}else if(cmd == '?'){
			int cnt = 0;
			// same length or longer than pattern
			pat = str;
			while(pat.size() <= 18){
				if(dict.find(pat) != dict.end()){
					cnt += dict.find(pat)->second;
				}
				pat = "0" + pat;
			}
			// shorter than pattern
			pat = str;
			while(pat.size() && ((pat[0] - '0') & 1) == 0){
				pat = pat.substr(1, pat.size()-1);
				if(dict.find(pat) != dict.end()){
					cnt += dict.find(pat)->second;
				}
			}
			cout << cnt << endl;
		}
	}

	return 0;
}
