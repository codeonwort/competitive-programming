// ID:  1655 (가운데를 말해요)
// URL: https://www.acmicpc.net/problem/1655
// Category: Priority Queue

#include <stdio.h>
#include <queue>
#include <vector>
#include <functional>
using namespace std;

int main() {
	int n;
	scanf("%d", &n);

	priority_queue<int> maxHeap;
	priority_queue<int, vector<int>, greater<int>> minHeap;
	for(int i=0; i<n; i++){
		int x;
		scanf("%d", &x);

		if(maxHeap.empty()){
			maxHeap.push(x);
		}else{
			int mid = maxHeap.top();
			if(mid < x) minHeap.push(x);
			else maxHeap.push(x);
			
			if(maxHeap.size() > minHeap.size() + 1){
				minHeap.push(maxHeap.top());
				maxHeap.pop();
			}else if(minHeap.size() > maxHeap.size()){
				maxHeap.push(minHeap.top());
				minHeap.pop();
			}
		}

		printf("%d\n", maxHeap.top());
	}

	return 0;
}
