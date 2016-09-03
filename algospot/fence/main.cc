#include <iostream>

using namespace std;

void solve();
int recurse(int fences[], int l, int r);

int main() {
	int c;
	cin >> c;
	while(c --> 0) solve();
	return 0;
}

void solve() {
	int n;
	int fences[20000];

	cin >> n;
	for(int i=0; i<n; i++) cin >> fences[i];

	int soln = recurse(fences, 0, n-1);
	cout << soln << endl;
}

// l and r are inclusive
int recurse(int fences[], int l, int r) {
	// base case
	if(l == r) return fences[l];

	int mid = (l+r)/2;
	
	int soln1 = recurse(fences, l, mid);
	int soln2 = recurse(fences, mid+1, r);

	int lo = mid, hi = mid+1;
	int width, height = min(fences[lo], fences[hi]);
	int soln3 = 2 * height;
	while(l < lo || hi < r){
		if(hi < r && (lo == l || fences[lo-1] < fences[hi+1])){
			// expand to right
			hi++;
			height = min(height, fences[hi]);
		}else{
			lo--;
			height = min(height, fences[lo]);
		}
		soln3 = max(soln3, height * (hi-lo+1));
	}
	
	return max(soln3, max(soln2, soln1));
}
