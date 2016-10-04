// ID:  DICTIONARY (고대어 사전)
// URL: https://algospot.com/judge/problem/read/DICTIONARY

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool edge[26][26];

void addEdge(string& a, string& b) {
	int n = min(a.size(), b.size());
	for(int i=0; i<n; i++){
		if(a[i] == b[i]) continue;
		edge[a[i]-'a'][b[i]-'a'] = true;
		break;
	}
}

void dfs(int v, vector<bool>& visited, vector<char>& order) {
	visited[v] = true;
	for(int u=0; u<26; u++){
		if(!visited[u] && edge[v][u]){
			dfs(u, visited, order);
		}
	}
	order.push_back('a' + v);
}
void tsort(vector<char>& order) {
	vector<bool> visited(26, false);
	for(int i=0; i<26; i++){
		if(!visited[i]) dfs(i, visited, order);
	}
	reverse(order.begin(), order.end());
	for(int i=0; i<order.size(); i++){
		for(int j=i+1; j<order.size(); j++){
			if(edge[order[j]-'a'][order[i]-'a']){
				order.clear(); return;
			}
		}
	}
}

void solve() {
	int n; // num words
	cin >> n;
	vector<string> words(n);
	for(int i=0; i<n; i++){
		cin >> words[i];
	}

	// initialize graph
	for(int i=0; i<26; i++){
		for(int j=0; j<26; j++){
			edge[i][j] = false;
		}
	}

	// add edges
	for(int i=0; i<n-1; i++){
		addEdge(words[i], words[i+1]);
	}

	// topological sort
	vector<char> order;
	tsort(order);
	if(order.size()){
		for(int i=0; i<order.size(); i++){
			cout << order[i];
		}
		cout << endl;
	}else{
		cout << "INVALID HYPOTHESIS" << endl;
	}
}

int main() {
	int tests;
	cin >> tests;
	while(tests --> 0) solve();
	return 0;
}
