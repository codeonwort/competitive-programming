// ID:  NERD2 (너드인가, 너드가 아닌가? 2)
// URL: https://algospot.com/judge/problem/read/NERD2

// note: Fucking iterator manipulation
//       I hate it

#include <iostream>
#include <map>
using namespace std;

void solve() {
	int n;
	map<int,int> dict;

	cin >> n;

	int sum = 0;
	for(int i=0; i<n; i++){
		int p, q;
		cin >> p >> q;

		auto it = dict.upper_bound(p);
		if(it == dict.end() || q > it->second){
			// new person can be a nerd
			dict[p] = q;
			// remove non-nerds
			it = dict.find(p);
			if(it != dict.begin()){
				it--;
				while(true){
					if(it->second < q){
						auto jt = it;
						if(it == dict.begin()){
							dict.erase(it);
							break;
						}else{
							jt--;
							dict.erase(it);
							it = jt;
						}
					}else break;
				}
			}
		}
		sum += dict.size();
	}

	cout << sum << endl;
}

int main() {
	int t;
	cin >> t;
	while(t --> 0) solve();
	return 0;
}
