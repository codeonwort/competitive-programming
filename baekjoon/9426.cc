// ID: 9426 (중앙값 측정)
// URL: https://www.acmicpc.net/problem/9426

#include <stdio.h>
#include <vector>
#include <set>
using namespace std;

// variables
vector<int> heats;
multiset<int> bag;
decltype(bag.begin()) center;
long long answer = 0;

int main() {
	// input
	int n, k;
	scanf("%d %d", &n, &k);
	heats.resize(n);
	for(int i=0; i<n; ++i) scanf("%d", &heats[i]);

	// solve
	for(int i=0; i<k; ++i) bag.insert(heats[i]);
	center = next(bag.begin(), (k+1)/2 - 1);
	answer += *center;

	for(int i=0; i<n-k; ++i){
		auto L = heats[i];
		auto R = heats[i+k];
		bag.insert(R);
		if(R < *center) --center;
		if(L <= *center) ++center;
		bag.erase(bag.lower_bound(L));
		answer += *center;
	}
	
	// output
	printf("%lld\n", answer);

	return 0;
}
