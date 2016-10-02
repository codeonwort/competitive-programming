// ID:  SOLONG (안녕히, 그리고 물고기는 고마웠어요!)
// URL: https://algospot.com/judge/problem/read/SOLONG
// Category: Trie

#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'A'; }
struct Trie {
	Trie* children[ALPHABETS];
	int first; // id of the word that visited this node at first
	int terminal; // id of the word that terminates here
	Trie() : terminal(-1), first(-1) {
		memset(children, 0, sizeof(children));
	}
	void add(const char* word, int id) {
		if(first == -1) first = id;
		if(*word == 0){
			terminal = id;
		}else{
			int next = toNumber(*word);
			if(children[next] == NULL) children[next] = new Trie();
			children[next]->add(word + 1, id);
		}
	}
	int query(char* word, int id) {
		if(*word == 0) return 0;
		if(first == id) return 1; // press tab
		int next = toNumber(*word);
		return 1 + children[next]->query(word + 1, id);
	}
	Trie* find(char* word) {
		if(*word == 0) return this;
		int next = toNumber(*word);
		if(children[next] == NULL) return NULL;
		return children[next]->find(word + 1);
	}
};

void solve() {
	int n, m;
	scanf("%d %d", &n, &m);

	// build dictionary
	char word[11];
	int freq;
	vector<pair<int,string> > input;
	for(int i=0; i<n; i++){
		scanf("%s %d", word, &freq);
		input.push_back(make_pair(-freq, word));
	}
	sort(input.begin(), input.end());

	Trie* root = new Trie();
	for(int i=0; i<input.size(); i++){
		root->add(input[i].second.c_str(), i);
	}
	root->first = -1;

	// query
	int count = m - 1;
	for(int i=0; i<m; i++){
		scanf("%s", word);
		Trie* node = root->find(word);
		// node = NULL			-> word is not in the dictionary
		// node->terminate = -1	-> word is just a part of a word in the dictionary
		// thus we have to fully type it
		if(node == NULL || node->terminal == -1) count += strlen(word);
		else count += root->query(word, node->terminal);
	}
	printf("%d\n", count);
}

int main() {
	int t;
	scanf("%d", &t);
	while(t --> 0) solve();
	return 0;
}
