// ID:  9184 (신나는 함수 실행)
// URL: https://www.acmicpc.net/problem/9184

#include <iostream>
#include <algorithm>
#include <stdio.h>
#define LL long long

/* lessons learned
WTF
output format is not just the answer, but w(a,b,c) = x
Read the problem carefully
 */

using namespace std;

bool evaluated[21][21][21];
LL dp[21][21][21];

LL get(int a, int b, int c) {
	if(a <= 0 || b <= 0 || c <= 0) return 1;
	if(a > 20 || b > 20 || c > 20) a = b = c = 20;
	return dp[a][b][c];
}
void eval(int a, int b, int c) {
	// out of bounds
	if(a <= 0 || b <= 0 || c <= 0) return;

	// already evaluated
	if(evaluated[a][b][c]) return;

	// common case
	if(a < b && b < c){
		eval(a, b, c-1);
		eval(a, b-1, c-1);
		eval(a, b-1, c);
		dp[a][b][c] = get(a,b,c-1) + get(a,b-1,c-1) - get(a,b-1,c);
	}else{
		eval(a-1, b-1, c);
		eval(a-1, b, c-1);
		eval(a-1, b, c);
		eval(a-1, b-1, c-1);
		dp[a][b][c] = get(a-1,b,c) + get(a-1,b-1,c) + get(a-1,b,c-1) - get(a-1,b-1,c-1);
	}
	evaluated[a][b][c] = true;
}

int main() {
	// DP table
	for(int i=0; i<=20; i++){
		for(int j=0; j<=20; j++){
			for(int k=0; k<=20; k++){
				dp[i][j][k] = -1;
				evaluated[i][j][k] = false;
			}
		}
	}

	// input & output
	while(1){
		int a,b,c, a1,b1,c1;
		cin >> a >> b >> c;
		a1 = a ; b1 = b ; c1 = c;
		if(a == -1 && b == -1 && c == -1) break;
		if(a <= 0 || b <= 0 || c <= 0) a = b = c = 0;
		if(a > 20 || b > 20 || c > 20) a = b = c = 20;
		eval(a,b,c);
		//cout << get(a,b,c) << endl;
		printf("w(%d, %d, %d) = %d\n", a1,b1,c1, get(a,b,c));
	}

	return 0;
}
