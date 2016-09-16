// ID:  10258 (스위치 배열)
// URL: https://www.acmicpc.net/problem/10258

#include <iostream>
#include <vector>
#include <string>
using namespace std;

void solve();

// S = b0 b1 b2 ... b[n-1]
// dp[i] = steps needed to make 00...0 -> 10...0 (leftmost is b[i])
// dp2[i] = steps needed to make 000...0 -> 110...0 (leftmost is b[i])
long long int dp[101];
long long int dp2[101];

int main() {
	int t;
	cin >> t;
	while(t --> 0) solve();
}

void solve() {
	string str;
	
	cin >> str;
	int n = str.size();

	for(int i=0; i<n; i++){
		dp[i] = (1 << (n-i)) - 1;
	}
	dp2[n-1] = 1;
	for(int i=0; i<n-1; i++){
		dp2[i] = dp[i+1] + 1;
	}

	long long int cnt = 0;
	for(int i=0; i<n-2; i++){
		if(str[i] == '0') continue;
		str[i] = '0';
		if(str[i+1] == '1'){
			cnt += dp2[i];
			str[i+1] = '0';
			i++;
		}else{
			cnt += dp2[i];
			str[i+1] = '1';
		}
	}
	if(str[n-2] == '0' && str[n-1] == '1') cnt += 1;
	else if(str[n-2] == '1' && str[n-1] == '1') cnt += 2;
	else if(str[n-2] == '1' && str[n-1] == '0') cnt += 3;

	cout << cnt << endl;
}
