// ID:  1920 (수 찾기)
// URL: https://www.acmicpc.net/problem/1920

// Manual implementation of merge sort and binary search just for exercise
// std::sort() and std::binary_search() in C++ "algorithm.h" work perfectly well

#include <stdio.h>
using namespace std;

int nums[100000];

void sort(int nums[], int left, int right); // sort in nondecreasing order
int binsearch(int nums[], int x, int l, int r); // 1 if exists, 0 otherwise

int main() {
	int n;

	// input
	scanf("%d", &n);
	for(int i=0; i<n; i++) scanf("%d", nums+i);

	sort(nums, 0, n-1);

	// sort debugging
	/*for(int i=0; i<n; i++){
		printf("%d ", nums[i]);
	}
	puts("");*/

	// queries
	int m,x;
	scanf("%d", &m);
	for(int i=0; i<m; i++){
		scanf("%d", &x);
		printf("%d\n", binsearch(nums, x, 0, n-1));
	}

	return 0;
}

// merge sort exercise
int temp[100000];
void sort(int nums[], int l, int r) {
	if(l >= r) return;

	int mid = (l+r)/2;

	// sub problem
	sort(nums, l, mid);
	sort(nums, mid+1, r);

	// merge
	int l1 = l, r1 = mid;
	int l2 = mid+1, r2 = r;
	int pos = 0;
	while(l1 <= r1 || l2 <= r2){
		if(l1 <= r1 && (l2 > r2 || nums[l1] <= nums[l2])){
			temp[pos] = nums[l1];
			l1++;
		}else if(l2 <= r2){
			temp[pos] = nums[l2];
			l2++;
		}
		pos++;
	}
	for(pos=0; pos<=r-l; pos++){
		nums[l+pos] = temp[pos];
	}
}

// binary search
int binsearch(int nums[], int x, int l, int r) {
	if(l > r) return 0;
	int mid = (l+r)/2;
	if(nums[mid] == x) return 1;
	if(x < nums[mid]) return binsearch(nums, x, l, mid-1);
	return binsearch(nums, x, mid+1, r);
}
