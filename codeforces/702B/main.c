#include <stdio.h>

int n;
int xs[100000 + 1];

int main() {
	int i, j, x, y, z, cnt = 0;

	scanf("%d", &n);
	for(i=0; i<n; i++){
		scanf("%d", xs + i);
	}

	for(i=0; i<n; i++){
		x = xs[i];
		for(j=i+1; j<n; j++){
			y = xs[j];
			z = x + y;
			if((z & (z-1)) == 0) cnt ++;
		}
	}

	printf("%d", cnt);

	return 0;
}
