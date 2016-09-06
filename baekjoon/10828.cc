// ID:  10828 (스택)
// URL: https://www.acmicpc.net/problem/10828

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	int n;
	string cmd;
	int arg;
	vector<int> stack;
	
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> cmd;
		if(cmd == "push"){
			cin >> arg;
			stack.push_back(arg);
		}else if(cmd == "pop"){
			if(stack.size() == 0) cout << -1 << endl;
			else{
				cout << stack.back() << endl;
				stack.pop_back();
			}
		}else if(cmd == "size"){
			cout << stack.size() << endl;
		}else if(cmd == "empty"){
			if(stack.size() == 0) cout << 1 << endl;
			else cout << 0 << endl;
		}else if(cmd == "top"){
			if(stack.size() == 0) cout << -1 << endl;
			else cout << stack.back() << endl;
		}
	}
}
