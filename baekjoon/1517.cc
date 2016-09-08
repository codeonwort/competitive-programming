// ID:  1517 (버블소트)
// URL: https://www.acmicpc.net/problem/1517

#include <stdio.h>
#include <algorithm>
#define LL long long
using namespace std;

/* Note
 * After this is accepted, I saw accepted codes others have wrotten.
 * They used just merge sort technique
 * And no binary search was performed during conquer step. WTH??
 */

// loser[i]: number of elements
//           s.t. loser[i] > loser[j] for all i < j
int loser[500000];
int ary[500000];

// calculate loser[start..end] from ary[start..end]
void recurse(int start, int end);
void join(int l1, int r1, int l2, int r2);

int main() {
	int n;

	// input
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		scanf("%d", ary + i);
		loser[i] = 0;
	}

	// solve
	LL soln = 0;
	recurse(0, n-1);
	for(int i=0; i<n; i++) soln += loser[i];

	// debug
	//for(int i=0; i<n; i++) printf("%d ", loser[i]);
	//puts("");

	// output
	printf("%lld\n", soln);

	return 0;
}

void recurse(int start, int end) {
	if(start == end){
		loser[start] = 0;
		return;
	}

	// divide
	int mid = (start + end) / 2;
	recurse(start, mid);
	recurse(mid+1, end);

	// conquer
	// - loser[start..mid] only considers ary[start..mid]
	//   ary[mid+1..end] have to be considered
	// - loser[mid+1..end] only needs to consider ary[mid+1..end]
	//   so conquer step is not needed
	join(start,mid, mid+1,end);
}

int temp[500000];
void join(int l1, int r1, int l2, int r2) {
	int n = r2 - l2 + 1;
	for(int i=0; i<n; i++) temp[i] = ary[l2 + i];
	sort(temp, temp + n);

	for(int i=l1; i<=r1; i++){
		int x = ary[i];

		// case: out of bounds
		if(x <= temp[0]) continue;
		if(x > temp[n-1]){
			loser[i] += n; continue;
		}

		// for each element in ary[l1..r1],
		//   count the number of losers in ary[l2..r2]
		int lo = 0, hi = n-1, mid;
		while(lo <= hi){
			mid = (lo + hi) / 2;
			if(x <= temp[mid]){
				hi = mid - 1;
			}else if(x > temp[mid]){
				lo = mid + 1;
			}
		}
		while(temp[mid] >= x) mid--;

		loser[i] += mid + 1;
	}
}

