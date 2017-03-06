// ID:  711A (Bus to Udayland)
// URL: http://codeforces.com/problemset/problem/711/A

#include <stdio.h>

int main() {
	int n;
	char seats[1000][4];
	char dummy;

	scanf("%d", &n);
	scanf("%c", &dummy);
	for(int i=0; i<n; i++){
		scanf("%c%c|%c%c", &seats[i][0], &seats[i][1], &seats[i][2], &seats[i][3]);
		scanf("%c", &dummy);
	}

	int row = -1, col = -1;
	for(int i=0; i<n; i++){
		if(seats[i][0] == 'O' && seats[i][1] == 'O'){
			row = i;
			col = 0;
			break;
		}
		if(seats[i][2] == 'O' && seats[i][3] == 'O'){
			row = i;
			col = 2;
			break;
		}
	}

	if(row == -1){
		puts("NO");
	}else{
		seats[row][col] = '+';
		seats[row][col+1] = '+';
		puts("YES");
		for(int i=0; i<n; i++){
			printf("%c%c|%c%c\n", seats[i][0], seats[i][1], seats[i][2], seats[i][3]);
		}
	}

	return 0;
}
