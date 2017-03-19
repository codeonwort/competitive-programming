// ID:  2110 (공유기 설치)
// URL: https://www.acmicpc.net/problem/2110

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

bool can(vector<int>& xs, int c, int dist) {
	int curr = 0;
	int dist_accum = 0;
	while(c > 0 && curr < xs.size()){
		dist_accum += xs[curr + 1] - xs[curr];
		if(dist_accum >= dist){
			--c;
			dist_accum = 0;
		}
		++curr;
	}
	return c == 0;
}

int main() {
	int n, c;
	scanf("%d %d", &n, &c);

	vector<int> xs(n);
	for(int i=0; i<n; ++i){
		scanf("%d", &xs[i]);
	}
	xs.push_back(2e9);

	sort(xs.begin(), xs.end());

	int bot = 1, top = 1e9;
	int cnt = 0;
	while(bot <= top && cnt++ < 40){
		int mid = (bot + top) / 2;
		if(can(xs, c, mid)) bot = mid + 1;
		else top = mid - 1;
	}

	printf("%d\n", bot - 1);

	return 0;
}
