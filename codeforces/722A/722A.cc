// ID:  722A (Broken Clock)
// URL: http://codeforces.com/problemset/problem/722/A

#include <iostream>
#include <string>
using namespace std;

int main() {
	int n;
	string s, hh, mm;

	cin >> n >> s;
	hh = s.substr(0, 2);
	mm = s.substr(3, 2);

	if(n == 12){
		if(hh[0] > '1'){
			if(hh[1] == '0') hh[0] = '1';
			else hh[0] = '0';
		}
		if(hh[0] == '1' && hh[1] > '2') hh[1] = '1';
		else if(hh[0] == '0' && hh[1] == '0') hh[1] = '1';
		if(mm[0] > '5') mm[0] = '5';
	}else{
		if(hh[0] > '2') hh[0] = '0';
		if(hh[0] == '2' && hh[1] > '3') hh[1] = '1';
		if(mm[0] > '5') mm[0] = '5';
	}

	cout << hh << ':' << mm << endl;
}
