// ID:  1298 (노트북의 주인을 찾아서)
// URL: https://www.acmicpc.net/problem/1298
// Category: Flow Network, Dinic Algorithm
 
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
 
const int INF = 987654321;
const int MAX = 202;
struct edge { int to, capacity, rev; };
vector<edge> G[MAX];    // graph as an adjacent list
int level[MAX];         // each vertex's distance from source
int iter[MAX];          // explore how far
bool connected[MAX][MAX];

void addEdge(int from, int to, int capacity) {
    if(connected[from][to]) return;
    connected[from][to] = true;
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

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
 
    // 0:           source
    // 1 ~ n:       students
    // n+1 ~ n+n:   laptops
    // n+n+1:       sink
    for(int i=0; i<m; i++){
        int student, laptop;
        scanf("%d %d", &student, &laptop);
        addEdge(0, student, 1);
        addEdge(student, n+laptop, 1);
        addEdge(n+laptop, n+n+1, 1);
    }

    int flow = max_flow(0, n+n+1);
    printf("%d\n", flow);
 
    return 0;
}
