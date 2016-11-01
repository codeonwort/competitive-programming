// ID:  11657 (타임머신)
// URL: https://www.acmicpc.net/problem/11657

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_E = 6000;
const int MAX_V = 500;
const int INF = 1e8;

struct edge { int from, to, cost; };
edge es[MAX_E];
int d[MAX_V];
int V, E;

bool bellman_ford(int start) {
	for(int i=0; i<V; i++) d[i] = INF;
	d[start] = 0;
	int loop = 0;
	while(true){
		bool update = false;
		for(int i=0; i<E; i++){
			edge& e = es[i];
			if(d[e.from] != INF && d[e.to] > d[e.from] + e.cost){
				d[e.to] = d[e.from] + e.cost;
				update = true;
			}
		}
		loop++;
		if(!update || loop >= V) break;
	}
	return loop < V;
}

void solve() {
	scanf("%d %d", &V, &E);
	for(int i=0; i<E; i++){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &es[i].cost);
		es[i].from = u - 1; es[i].to = v - 1;
	}

	if(bellman_ford(0)){
		for(int i=1; i<V; i++){
			printf("%d\n", d[i] == INF ? -1 : d[i]);
		}
	}else{
		puts("-1");
	}
}

int main() {
	solve();
	return 0;
}
