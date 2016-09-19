// ID:  2985 (세 수)
// URL: https://www.acmicpc.net/problem/2985

#include <stdio.h>
#include <iostream>
using namespace std;

int main() {
	int a, b, c;

	cin >> a >> b >> c;

	if(a + b == c){
		printf("%d+%d=%d\n", a,b,c);
	}else if(a - b == c){
		printf("%d-%d=%d\n", a,b,c);
	}else if(a * b == c){
		printf("%d*%d=%d\n", a,b,c);
	}else if(a / b == c){
		printf("%d/%d=%d\n", a,b,c);
	}else if(a == b + c){
		printf("%d=%d+%d\n", a,b,c);
	}else if(a == b - c){
		printf("%d=%d-%d\n", a,b,c);
	}else if(a == b * c){
		printf("%d=%d*%d\n", a,b,c);
	}else{
		printf("%d=%d/%d\n", a,b,c);
	}

	return 0;
}
