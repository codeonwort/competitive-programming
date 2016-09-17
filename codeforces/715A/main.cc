// ID:  715A (Plus and Square Root)
// URL: http://codeforces.com/problemset/problem/715/A

#include <iostream>
#include <cmath>
using namespace std;

int main() {
	long long int n;

	cin >> n;

	long long int x = 2;
	for(long long int i=1; i<=n; i++){
		/* debug
		cout << "x: " << x;
		if(i == 1) x += 2;
		else x += i * ((i+1)*(i+1)*i - i + 1);
		cout << " -> " << x;
		x = sqrt(x);
		cout << " -> " << x << endl;
		*/
		if(i == 1) cout << 2 << endl;
		else cout << (i+1)*(i+1)*i - i + 1 << endl;
	}

	return 0;
}
