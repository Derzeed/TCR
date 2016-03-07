#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define PB(a) push_back(a)
#define MP(a,b) make_pair(a,b)

typedef long long ll;

const ll INF = 1 << 31 - 1;

struct Edge {
  ll flow, capacity;
  int from, to, index;
  Edge(int from, int to, ll capacity, int index) :
    from(from), to(to), capacity(capacity), index(index), flow(0) {}
};

struct EdmondsKarp {
  vector<vector<Edge> > edges;

  EdmondsKarp(int nrNodes) {
    edges = vector<vector<Edge> >(nrNodes);
  }

  void addEdge(int from, int to, ll capacity) {
    edges[from].PB(Edge(from, to,   capacity, edges[to].size()));
    if(from == to) ++edges[from].back().index;
    edges[to].  PB(Edge(to,   from, 0,        edges[from].size()-1));
  }

  ll findFlow(int s, int t) {
    vector<Edge *> dad(edges.size(), NULL);
    queue<int> q;
    q.push(s);

    while(!q.empty()) {
      int node = q.front();
      // cout << "Node: " << node << endl;
      q.pop();

      for(Edge &e : edges[node]) {
        // cout << "To: " << e.to << endl;
        // cout << "Capacity: " << e.capacity << endl;
        if(e.capacity - e.flow > 0 && dad[e.to] == NULL && e.to != s) {
          dad[e.to] = &e;
          q.push(e.to);
        }
      }
    }

    if(dad[t] == NULL) return 0;

    ll flow = INF;
    for(Edge* e = dad[t]; e != NULL; e = dad[e->from]) {
      flow = min(flow, e->capacity - e->flow);
    }

    for(Edge* e = dad[t]; e != NULL; e = dad[e->from]) {
      e->flow += flow;
      edges[e->to][e->index].flow -= flow;
    }
    
    return flow;
  }

  ll maxFlow(int s, int t) {
    ll totFlow = 0;
    while(int flow = findFlow(s, t)) {
      // cout << "Flow: " << flow << endl << endl;
      totFlow += flow;
    }
    return totFlow;
  }
};

int main() {
  int N, M;

  cin >> N >> M;

  EdmondsKarp instance(N+1);

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