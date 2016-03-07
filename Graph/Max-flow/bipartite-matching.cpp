#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

#define PB(a) push_back(a)

typedef long long ll;

const ll INF = numeric_limits<ll>::max();

struct Edge {
  ll flow, capacity;
  int from, to, index;
  Edge(int from, int to, ll capacity, int index) :
    from(from), to(to), capacity(capacity), index(index), flow(0) {}
};

struct Dinic {
  vector<vector<Edge> > edges;
  vector<int> level;

  Dinic(int N) : edges(N), level(N) {}

  void addEdge(int from, int to, ll capacity) {
    if(from == to) return;
    edges[from].PB(Edge(from, to,   capacity, edges[to].size()));
    edges[to].  PB(Edge(to,   from, 0,        edges[from].size()-1));
  }

  ll blokingFlow(int s, int node, ll flow) {
    if(node == s) return flow;

    ll totFlow = 0;
    for(Edge &edge : edges[node]) if(level[node] == 1 + level[edge.to]) {
      Edge &e = edges[edge.to][edge.index];
      if(e.capacity - e.flow > 0) {
        if(ll tmp = blokingFlow(s, e.from, min(flow, e.capacity - e.flow))) {
          e.flow += tmp;
          edge.flow -= tmp;
          flow -= tmp;
          totFlow += tmp;
        }
      }

      if(flow == 0) {
        break;
      }
    }


    return totFlow;
  }

  bool createLevelGraph(int s, int t) {
    fill(level.begin(), level.end(), -1);
    queue<int> q;
    q.push(s);
    level[s] = 0;

    while(!q.empty()) {
      int node = q.front();
      q.pop();

      if(node == t) return true;

      for(Edge &e : edges[node]) {
        if(e.capacity - e.flow > 0 && level[e.to] == -1) {
          level[e.to] = level[node]+1;
          q.push(e.to);
        }
      }
    }

    return false;
  }

  ll maxFlow(int s, int t) {
    ll totFlow = 0;
    while(createLevelGraph(s, t)) {
      totFlow += blokingFlow(s, t, INF);
    }
    return totFlow;
  }
};

int main() {
  int N, M, P;

  cin >> N >> M >> P;

  Dinic instance(N+M+2);

  while(P --> 0) {
    int A, B;
    cin >> A >> B;
    instance.addEdge(A, N+B, 1);
  }
  for(int i = 1; i <= N; ++i) instance.addEdge(0,   i,     1);
  for(int i = 1; i <= M; ++i) instance.addEdge(N+i, N+M+1, 1);

  cout << instance.maxFlow(0, N+M+1);
  return 0;
}