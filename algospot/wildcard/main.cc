// ID:  WILDCARD
// URL: https://algospot.com/judge/problem/read/WILDCARD

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

bool dp[100][100];

void solve();
bool match(string&, string&);

int main() {
	int c;
	cin >> c;
	while(c --> 0) solve();
}

void solve() {
	string pattern, word;
	int n;
	vector<string> matches;

	cin >> pattern;
	cin >> n;
	while(n --> 0){
		cin >> word;
		if(match(pattern, word)){
			matches.push_back(word);
		}
	}
	sort(matches.begin(), matches.end());

	for(int i=0; i<matches.size(); i++){
		cout << matches[i] << endl;
	}
}

bool match(string& pattern, string& word) {
	int n = pattern.size();
	int m = word.size();

	// initial solution
	char p = pattern[0];
	dp[0][0] = p == '*' || p == '?' || p == word[0];
	for(int i=1; i<n; i++){
		bool allstar = true;
		p = pattern[i];
		for(int j=0; j<i; j++){
			if(pattern[j] != '*'){
				allstar = false; break;
			}
		}
		dp[i][0] = (dp[i-1][0] && p == '*') ||
					(allstar && (p == '?' || p == word[0]));
	}
	for(int i=1; i<m; i++){
		dp[0][i] = pattern[0] == '*';
	}

	// DP
	for(int i=1; i<n; i++){
		for(int j=1; j<m; j++){
			p = pattern[i];
			if(p == '*'){
				dp[i][j] = dp[i-1][j-1] || dp[i-1][j] || dp[i][j-1];
			}else if(p == '?'){
				dp[i][j] = dp[i-1][j-1];
			}else{
				dp[i][j] = dp[i-1][j-1] && p == word[j];
			}
		}
	}

	return dp[n-1][m-1];
}
