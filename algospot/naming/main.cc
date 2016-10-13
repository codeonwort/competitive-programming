#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<int> getPartialMatch(const string& str) {
	int m = str.size();
	vector<int> pi(m, 0);

	int begin = 1, matched = 0;
	while(begin + matched < m){
		if(str[begin + matched] == str[matched]){
			matched++;
			pi[begin+matched-1] = matched;
		}else{
			if(matched == 0) begin++;
			else{
				begin += matched - pi[matched-1];
				matched = pi[matched-1];
			}
		}
	}
	return pi;
}

int main() {
	string mother, father, str;
	cin >> father >> mother;

	str = father + mother;
	vector<int> pi = getPartialMatch(str);

	int k = str.size();
	vector<int> answer;
	while(k > 0){
		answer.push_back(k);
		k = pi[k-1];
	}

	for(int i = answer.size()-1; i>=0; i--){
		cout << answer[i] << ' ';
	}

	return 0;
}
