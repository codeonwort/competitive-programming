// ID:  711B (Chris and Magic Square)
// URL: http://codeforces.com/problemset/problem/711/B

#include <stdio.h>

#define MAX 500
#define LL long long

LL sumRow(LL table[MAX][MAX], int n, int row) {
	LL sum = 0;
	for(int j=0; j<n; j++) sum += table[row][j];
	return sum;
}

LL sumCol(LL table[MAX][MAX], int n, int col) {
	LL sum = 0;
	for(int i=0; i<n; i++) sum += table[i][col];
	return sum;
} 
LL sumDiagonal(LL table[MAX][MAX], int n) {
	LL sum = 0;
	for(int i=0; i<n; i++) sum += table[i][i];
	return sum;
}

LL sumDiagonal2(LL table[MAX][MAX], int n) {
	LL sum = 0;
	for(int i=0; i<n; i++) sum += table[i][n-i-1];
	return sum;
}


int main() {
	int n;
	LL table[MAX][MAX];
	char dummy;

	scanf("%d", &n);
	scanf("%c", &dummy);

	// special case
	if(n == 1){
		puts("1");
		return 0;
	}

	int y,x;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			scanf("%lld", &table[i][j]);
			//scanf("%I64d", &table[i][j]);
			if(table[i][j] == 0){
				y = i; x = j;
			}
		}
		scanf("%c", &dummy);
	}

	// row sum test
	LL rowSum = -1;
	for(int i=0; i<n; i++){
		if(i == y) continue;
		rowSum = sumRow(table, n, i);
		break;
	}
	
	LL soln = rowSum - sumRow(table, n, y);
	table[y][x] = soln;

	bool valid = soln > 0;
	for(int i=0; i<n; i++){
		if(sumRow(table, n, i) != rowSum){ valid = false; break; }
		if(sumCol(table, n, i) != rowSum){ valid = false; break; }
	}
	if(sumDiagonal(table, n) != rowSum){ valid = false; }
	if(sumDiagonal2(table, n) != rowSum){ valid = false; }

	if(valid){
		//printf("%I64d\n", soln);
		printf("%lld\n", soln);
	}else{
		puts("-1");
	}

	return 0;
}
