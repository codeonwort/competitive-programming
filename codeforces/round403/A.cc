// Codeforces Round #403 (Div. 2)
// A. Andryusha and Socks
// http://codeforces.com/contest/782/problem/A

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n;
	scanf("%d", &n);

	vector<bool> table(n, false);
	int answer = 0;
	int curr = 0;

	for(int i=0; i<n*2; ++i){
		int x;
		scanf("%d", &x);
		
		if(table[x]){
			curr -= 1;
		}else{
			table[x] = true;
			curr += 1;
			answer = max(answer, curr);
		}
	}

	printf("%d\n", answer);

	return 0;
}
