// ID:  QUADTREE
// URL: https://algospot.com/judge/problem/read/QUADTREE

#include <iostream>
#include <string>

using namespace std;

void solve();
string reverse(string::iterator& it);

int main() {
	int t;
	cin >> t;
	while(t --> 0) solve();
	return 0;
}

void solve() {
	string img;

	cin >> img;

	string::iterator it = img.begin();
	cout << reverse(it) << endl;
}

string reverse(string::iterator& it) {
	char head = *it;
	it++;
	if(head == 'b' || head == 'w'){
		return string(1, head);
	}
	string topLeft = reverse(it);
	string topRight = reverse(it);
	string bottomLeft = reverse(it);
	string bottomRight = reverse(it);
	return string("x") + bottomLeft + bottomRight + topLeft + topRight;
}
