// Codeforces Round #379 (Div. 2)
// http://codeforces.com/contest/734

// ID: 734D (Anton and Chess)

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

struct Coord { char type; int x, y; };
	Coord king;	
	vector<Coord> blacks, attackers;

bool lessX(Coord& a, Coord& b) { return a.x < b.x; }
bool lessY(Coord& a, Coord& b) { return a.y < b.y; }
bool greaterX(Coord& a, Coord& b) { return a.x > b.x; }
bool greaterY(Coord& a, Coord& b) { return a.y > b.y; }
using Sort = bool (*)(Coord&, Coord&);

void choose(int dx, int dy, Sort sortFn) {
	vector<Coord> candidates;
	// filter
	for(int i=0; i<blacks.size(); i++){
		int diffX = blacks[i].x - king.x;
		int diffY = blacks[i].y - king.y;
		bool ok = false;
		if(dx == 0) ok = diffX == 0 && diffY / dy >= 1;
		else if(dy == 0) ok = diffY == 0 && diffX / dx >= 1;
		else{
			int ry = diffY / dy, rx = diffX / dx;
			ok = ry >= 1 && rx >= 1 && ry == rx;
		}
		if(ok) candidates.push_back(blacks[i]);
	}
	if(candidates.size() == 0) return;
	// sort
	sort(candidates.begin(), candidates.end(), sortFn);
	attackers.push_back(candidates[0]);
}

bool checkmate(Coord& black, Coord& king) {
	int dx = black.x - king.x;
	int dy = black.y - king.y;
	if(black.type == 'R' || black.type == 'Q'){
		if(dx == 0 || dy == 0) return true;
	}
	if(black.type == 'B' || black.type == 'Q'){
		if(dy != 0 && abs(dx/dy) == 1) return true;
	}
	return false;
}

void solve() {
	// input
	int n;
	scanf("%d", &n);
	scanf("%d %d", &king.x, &king.y);
	for(int i=0; i<n; i++){
		Coord black;
		char buf[3];
		scanf("%s %d %d", buf, &black.x, &black.y);
		black.type = buf[0];
		blacks.push_back(black);
	}

	// select only nearest attackers for 8 directions
	choose(-1, -1, greaterX);  choose(0, -1, greaterY);  choose(1, -1, lessX);
	choose(-1, 0, greaterX);                             choose(1, 0, lessX);
	choose(-1, 1, greaterX);   choose(0, 1, lessY);      choose(1, 1, lessX);

	// check
	for(int i=0; i<attackers.size(); i++){
		if(checkmate(attackers[i], king)){
			puts("YES");
			return;
		}
	}
	puts("NO");
}

int main() {
	solve();
	return 0;
}
