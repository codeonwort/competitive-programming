// ID:  14433 (한조 대기 중)
// URL: https://www.acmicpc.net/problem/14433
// Category: Flow Network, Dinic Algorithm

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
 
const int INF = 987654321;
const int MAX = 802;     // 필요한 정점 개수만큼 조정
struct edge { int to, capacity, rev; };
vector<edge> G[MAX];    // graph as an adjacent list
int level[MAX];         // each vertex's distance from source
int iter[MAX];          // explore how far
 
// 간선 u -> v를 추가하면 capacity 0인 역간선 v -> u도 추가된다
// e = G[i][j]라 하면 e의 역간선은 G[e.to][e.rev]
void addEdge(int from, int to, int capacity) {
   G[from].push_back((edge){to, capacity, G[to].size()});
   G[to].push_back((edge){from, 0, G[from].size()-1});
}
 
// for each vertex, calculate the shortest distance from s into level[]
void bfs(int s) {
   memset(level, -1, sizeof(level));
   queue<int> q;
   level[s] = 0;
   q.push(s);
   while(!q.empty()){
       int v = q.front(); q.pop();
       for(int i=0; i<G[v].size(); i++){
           edge& e = G[v][i];
           if(e.capacity > 0 && level[e.to] < 0){
               level[e.to] = level[v] + 1;
               q.push(e.to);
           }
       }
   }
}
 
// Find an augmenting path using DFS
int dfs(int v, int t, int f) {
   if(v == t) return f;
   for(int& i = iter[v]; i < G[v].size(); i++){
       edge& e = G[v][i];
       if(e.capacity > 0 && level[v] < level[e.to]){
           int d = dfs(e.to, t, min(f, e.capacity));
           if(d > 0){
               e.capacity -= d;
               G[e.to][e.rev].capacity += d;
               return d;
           }
       }
   }
   return 0;
}
 
// s에서 t로 가는 max flow 구하기
// 간선마다 flow를 따로 유지하지 않고 capacity를 직접 수정한다
// 그래프 재활용할 때 주의
int max_flow(int s, int t) {
   int flow = 0;
   while(true){
       bfs(s);
       if(level[t] < 0) return flow;
       memset(iter, 0, sizeof(iter));
       int f;
       while((f = dfs(s, t, INF)) > 0){
           flow += f;
       }
   }
}

void clear_network() {
	for(int i=0; i<MAX; i++){
		G[i].clear();
	}
}

int solve(int n, int m, int k) {
   // 0:           source
   // 1 ~ n:       players
   // n+1 ~ n+m:   wanted troll heroes
   // n+m+1:       sink
   for(int i=1; i<=n; i++){
       addEdge(0, i, 1);
	}
	for(int i=1; i<=k; i++){
		int player, troll;
		scanf("%d %d", &player, &troll);
		addEdge(player, n + troll, 1);
	}
   for(int i=n+1; i<=n+m; i++){
       addEdge(i, n+m+1, 1);
   }

	return max_flow(0, n+m+1);
}
 
int main() {
	int n,m,k1,k2;
	scanf("%d %d %d %d", &n, &m, &k1, &k2);
	int a = solve(n, m, k1);
	clear_network();
	int b = solve(n, m, k2);
	puts(a >= b ? "그만 알아보자" : "네 다음 힐딱이");
	return 0;
}
