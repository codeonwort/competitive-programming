// ID:  10816 (숫자 카드 2)
// URL: https://www.acmicpc.net/problem/10816

#include <stdio.h>
#include <string.h>
#include <map>
#include <algorithm>
using namespace std;

const int MAX = 500000;
int num[MAX], cnt[MAX];

int main() {
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++) scanf("%d", num + i);

	map<int,int> mapping;
	memset(cnt, 0, sizeof(cnt));
	sort(num, num+n);
	int x = 0;
	mapping.insert(make_pair(num[0], 0));
	for(int i=0; i<n; i++){
		if(i > 0 && num[i] != num[i-1]){
			x++;
			mapping.insert(make_pair(num[i], x));
		}
		cnt[x]++;
	}

	int m;
	scanf("%d", &m);
	for(int i=0; i<m; i++){
		int x;
		scanf("%d", &x);
		if(mapping.find(x) == mapping.end()) printf("0 ");
		else printf("%d ", cnt[mapping[x]]);
	}

	return 0;
}
