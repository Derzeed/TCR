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
  vector<int> full;

  Dinic(int N) : edges(N), level(N), full(N) {}

  void addEdge(int from, int to, ll capacity) {
    if(from == to) return;
    edges[from].PB(Edge(from, to,   capacity, edges[to].size()));
    edges[to].  PB(Edge(to,   from, 0,        edges[from].size()-1));
  }

  ll blokingFlow(int node, int t, ll flow) {
    if(node == t) return flow;

    ll totFlow = 0;
    for(Edge &edge : edges[node]) if(level[node] + 1 == level[edge.to] && !full[edge.to]) {
      Edge &e = edges[edge.to][edge.index];
      if(edge.capacity - edge.flow > 0) {
        if(ll tmp = blokingFlow(edge.to, t, min(flow, edge.capacity - edge.flow))) {
          edge.flow += tmp;
          e.flow -= tmp;
          flow -= tmp;
          totFlow += tmp;
        }
      }

      if(flow == 0) {
        break;
      }
    }

    if(flow != 0) {
      full[node] = true;
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
      fill(full.begin(), full.end(), false);
      totFlow += blokingFlow(s, t, INF);
    }
    return totFlow;
  }
};

int main() {
  int N, M;

  cin >> N >> M;

  Dinic instance(N+1);

  for(int i = 0; i < M; ++i) {
    int from, to;
    ll capacity;
    cin >> from >> to >> capacity;
    instance.addEdge(from, to, capacity);
    instance.addEdge(to, from, capacity);
  }

  cout << instance.maxFlow(1, N) << endl;

  return 0;
}