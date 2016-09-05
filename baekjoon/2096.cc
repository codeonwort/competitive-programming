// ID:  2096 (내려가기)
// URL: https://www.acmicpc.net/problem/2096

/* == Lessons learned ==
 * Memory limit is very tight (only 4MB)
 * If we set dp[i][j]: optimal solution of tile[0..i]
 *                     where previous tile was j
 * Then memory limit is reached.
 *
 * 300,000 integers of 32-bit takes 1.14MB
 */

#include <algorithm>
#include <iostream>
using namespace std;

// dpMin[i], dpMax[i]: minimum/maximum cost where previous tile is
//                     i == 0: left
//                     i == 1: right
//                     i == 2: middle
int dpMin[3], dpMax[3];
int score[100000][3];

int main() {
	int n;

	// input
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> score[i][0] >> score[i][1] >> score[i][2];
	}

	// initial solution
	for(int i=0; i<3; i++){
		dpMax[i] = dpMin[i] = score[0][i];
	}

	// DP
	for(int i=1; i<n; i++){
		int min0 = score[i][0] + min(dpMin[0], dpMin[1]);
		int min1 = score[i][1] + min(min(dpMin[0], dpMin[1]), dpMin[2]);
		int min2 = score[i][2] + min(dpMin[1], dpMin[2]);
		dpMin[0] = min0; dpMin[1] = min1; dpMin[2] = min2;

		int max0 = score[i][0] + max(dpMax[0], dpMax[1]);
		int max1 = score[i][1] + max(max(dpMax[0], dpMax[1]), dpMax[2]);
		int max2 = score[i][2] + max(dpMax[1], dpMax[2]);
		dpMax[0] = max0; dpMax[1] = max1; dpMax[2] = max2;
	}

	// output
	int solnMax = max(max(dpMax[0], dpMax[1]), dpMax[2]);
	int solnMin = min(min(dpMin[0], dpMin[1]), dpMin[2]);
	cout << solnMax << ' ' << solnMin << endl;

	return 0;
}
