// Codeforces Round #403 (Div. 2)
// B. The Meeting Place Cannot Be Changed
// http://codeforces.com/contest/782/problem/B

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

vector<double> coords, speeds;

bool canMeet(double t){
	double L1 = coords[0] - speeds[0] * t;
	double R1 = coords[0] + speeds[0] * t;

	for(int i=1; i<coords.size(); ++i){
		double L2 = coords[i] - speeds[i] * t;
		double R2 = coords[i] + speeds[i] * t;
		L1 = max(L1, L2);
		R1 = min(R1, R2);
		if(L1 > R1) return false;
	}
	
	return true;
}

int main() {
	int n;
	scanf("%d", &n);

	coords.resize(n);
	speeds.resize(n);
	for(int i=0; i<n; ++i) scanf("%lf", &coords[i]);
	for(int i=0; i<n; ++i) scanf("%lf", &speeds[i]);

	double lb = 0.0, ub = 1e9;
	for(int i=0; i<100; ++i){
		double mid = (lb + ub) / 2;
		if(canMeet(mid)){
			ub = mid;
		}else{
			lb = mid;
		}
	}

	double answer = (lb + ub) / 2;
	printf("%.16lf\n", answer);

	return 0;
}
