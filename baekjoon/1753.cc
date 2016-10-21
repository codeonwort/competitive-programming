// ID:  1753 (최단경로)
// URL: https://www.acmicpc.net/problem/1753
// Category: Dijkstra Algorithm

#include <stdio.h>
#include <algorithm>
#include <queue>
#include <functional>
using namespace std;

struct edge { int to, cost; };
typedef pair<int,int> P;
const int MAX = 20002;
const int INF = 1e8;

vector<edge> G[MAX];
int dist[MAX];  	// min distance
int V;          	// num nodes

void dijkstra(int start) {
	priority_queue<P, vector<P>, greater<P> > Q;
	for(int i=0; i<V; i++) dist[i] = INF;
	dist[start] = 0;
	Q.push(P(0, start));
 
	while(!Q.empty()){
		P p = Q.top(); Q.pop();
		int v = p.second;
		if(dist[v] < p.first) continue;
		for(int i=0; i<G[v].size(); i++){
			edge e = G[v][i];
            if(dist[e.to] > dist[v] + e.cost){
               	dist[e.to] = dist[v] + e.cost;
                Q.push(P(dist[e.to], e.to));
            }
        }
   	}
}

int main() {
	int numV, numE, k;
	scanf("%d %d %d", &numV, &numE, &k);
	k--;
	V = numV;

	for(int i=0; i<numE; i++){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		u--; v--;
		edge e = {v, w};
		G[u].push_back(e);
	}
	dijkstra(k);

	for(int i=0; i<numV; i++){
		if(dist[i] == INF) puts("INF");
		else printf("%d\n", dist[i]);
	}

	return 0;
}
