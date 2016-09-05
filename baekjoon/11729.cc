// ID:  11729 (하노이 탑 이동 순서)
// URL: https://www.acmicpc.net/problem/11729

/* = Lessons leanred =
 * printing 100 millions of pairs
 * cout: over 3s
 * printf: just 0.2s
 */

#include <stdio.h>

// largest block: block[n]
// smallest block: block[1]
// move block[1..n] from poll 'prev' to poll 'next'
// poll: 1(left), 2(middle), 3(right)
void hanoi(int i, int prev, int next) {
	if(i == 0) return;
	int temp = 6 - prev - next;

	// move block[1..i-1] from prev to temp
	hanoi(i-1, prev, temp);

	// move block[i] from prev to next
	printf("%d %d\n", prev, next);

	// move block[1..i-1] from temp to next
	hanoi(i-1, temp, next);
}

int main() {
	int n;

	scanf("%d", &n);

	int moveCount = (2 << (n-1)) - 1;
	printf("%d\n", moveCount);

	hanoi(n, 1, 3);	

	return 0;

}
