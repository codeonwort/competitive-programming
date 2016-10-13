// ID:  BSHEEP (Build the Fence)
// URL: http://www.spoj.com/problems/BSHEEP/
// Category: Convex Hull

// Convex hull code from: https://github.com/jaehyunp/stanfordacm/blob/master/code/ConvexHull.cc

#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

typedef double T;
const T EPS = 1e-7;
struct PT { 
  T x, y;
  int id;
  PT() {} 
  PT(T x, T y) : x(x), y(y) {}
  bool operator<(const PT &rhs) const { return make_pair(y,x) < make_pair(rhs.y,rhs.x); }
  bool operator==(const PT &rhs) const { return make_pair(y,x) == make_pair(rhs.y,rhs.x); }
};

T cross(PT p, PT q) { return p.x*q.y-p.y*q.x; }
T area2(PT a, PT b, PT c) { return cross(a,b) + cross(b,c) + cross(c,a); }

double distance(const PT& p, const PT& q) {
	double dx = p.x - q.x, dy = p.y - q.y;
	return sqrt(dx*dx + dy*dy);
}

#ifdef REMOVE_REDUNDANT
bool between(const PT &a, const PT &b, const PT &c) {
  return (fabs(area2(a,b,c)) < EPS && (a.x-b.x)*(c.x-b.x) <= 0 && (a.y-b.y)*(c.y-b.y) <= 0);
}
#endif

void ConvexHull(vector<PT> &pts) {
  sort(pts.begin(), pts.end());
  pts.erase(unique(pts.begin(), pts.end()), pts.end());
  vector<PT> up, dn;
  for (int i = 0; i < pts.size(); i++) {
    while (up.size() > 1 && area2(up[up.size()-2], up.back(), pts[i]) >= 0) up.pop_back();
    while (dn.size() > 1 && area2(dn[dn.size()-2], dn.back(), pts[i]) <= 0) dn.pop_back();
    up.push_back(pts[i]);
    dn.push_back(pts[i]);
  }
  pts = dn;
  for (int i = (int) up.size() - 2; i >= 1; i--) pts.push_back(up[i]);
  
#ifdef REMOVE_REDUNDANT
  if (pts.size() <= 2) return;
  dn.clear();
  dn.push_back(pts[0]);
  dn.push_back(pts[1]);
  for (int i = 2; i < pts.size(); i++) {
    if (between(dn[dn.size()-2], dn[dn.size()-1], pts[i])) dn.pop_back();
    dn.push_back(pts[i]);
  }
  if (dn.size() >= 3 && between(dn.back(), dn[0], dn[1])) {
    dn[0] = dn.back();
    dn.pop_back();
  }
  pts = dn;
#endif
}

void solve() {
	int n; // num sheeps
	scanf("%d", &n);

	// input
	vector<PT> ps;
	for(int i=1; i<=n; i++){
		PT p;
		scanf("%lf %lf", &p.x, &p.y);
		p.id = i;
		ps.push_back(p);
	}

	// solve
	ConvexHull(ps);
	double len = 0.0;
	for(int i=0; i<ps.size()-1; i++){
		len += distance(ps[i], ps[i+1]);
	}
	if(ps.size() >= 2) len += distance(ps[ps.size()-1], ps[0]);

	// output
	printf("%.2lf\n", len);
	for(int i=0; i<ps.size(); i++){
		printf("%d ", ps[i].id);
	}
	puts("");
}

int main() {
	int tests;
	scanf("%d", &tests);
	while(tests --> 0) solve();
	return 0;
}
