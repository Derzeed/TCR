#include <bits/stdc++.h>
using namespace std;

#define PB(a) push_back(a)
#define MP(a, b) make_pair(a, b)

typedef long long ll;
typedef long long ld;

const ll INF_ll = numeric_limits<ll>::max();
const ld INF_ld = numeric_limits<ld>::max()/4;

struct Edge {
  ll flow, capacity;
  ld cost;
  int from, to, index;
  Edge(int from, int to, ll capacity, ld cost, int index) :
    from(from), to(to), capacity(capacity), cost(cost), index(index), flow(0) {}
};

struct LeviticFlow { // O(N^2M^2) (O(N^2*M*log(M)))
  vector<vector<Edge> > edges;
  vector<Edge *> dad;
  vector<bool> used;
  vector<ld> d;
  vector<int> id;

  LeviticFlow(int N) : edges(N), pi(N), dad(N), used(N), d(N), id(N) {}

  void addEdge(int from, int to, ll capacity, ld cost) {
    edges[from].PB(Edge(from, to,   capacity, cost,  edges[to].size()));
    if(from == to) ++edges[from].back().index;
    edges[to].  PB(Edge(to,   from, 0,        -cost, edges[from].size()-1));
  }

  pair<ll, ld> findShortestPath(int s, int t) {
    fill(dad.begin(), dad.end(), (Edge *)NULL);
    fill(id.begin(), id.end(), 0);
    fill(d.begin(), d.end(), INF_ld);
    d[s] = 0;
    deque<int> q;
    q.push_back (s);

    while (!q.empty()) {
      int v = q.front();
      q.pop_front();
      id[v] = 1;
      for (Edge& e : edges[v]) {
        if (e.flow < e.capacity && d[e.to] > d[v] + e.cost) {
          d[e.to] = d[v] + e.cost;
          if (id[e.to] == 0) q.push_back (e.to);
          else if (id[e.to] == 1) q.push_front (e.to);
          dad[e.to] = &e;
          id[e.to] = 1;
        }
      }
    }
    if(!id[t]) return MP(0, 0);

    ll flow = INF_ll;
    for(Edge *e = dad[t]; e != NULL; e = dad[e->from]) {
      flow = min(flow, e->capacity - e->flow);
    }

    ld cost = 0;
    for(Edge *e = dad[t]; e != NULL; e = dad[e->from]) {
      e->flow += flow;
      edges[e->to][e->index].flow -= flow;
      cost += flow*e->cost;
    }

    return MP(flow, cost);
  }

  pair<ll, ld> minCostMaxFlow(int s, int t) {
    ll maxF = 0;
    ld minC = 0;
    while(true) {
      pair<ll, ld> path = findShortestPath(s, t);
      if(path.first == 0) break;
      maxF += path.first;
      minC += path.second;
    }

    return MP(maxF, minC);
  }
};

int main() { // Tested on https://open.kattis.com/problems/mincostmaxflow
  int n, m, s, t;
  cin >> n >> m >> s >> t;
  LeviticFlow instance(n);
  for(int i = 0; i < m; i++) {
    int from, to, capacity, cost;
    cin >> from >> to >> capacity >> cost;
    instance.addEdge(from,to,capacity,cost);
  }

  ll flow;
  ld cost;
  tie(flow,cost) = instance.minCostMaxFlow(s,t);
  cout << flow << " " << cost << endl;
  return 0;
}
