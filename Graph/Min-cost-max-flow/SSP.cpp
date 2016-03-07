#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

#define PB(a) push_back(a)
#define MP(a, b) make_pair(a, b)

typedef long long ll;
typedef long double ld;

const ll INF_ll = numeric_limits<ll>::max();
const ld INF_ld = numeric_limits<ld>::max()/4;

struct Edge {
  ll flow, capacity;
  ld cost;
  int from, to, index;
  Edge(int from, int to, ll capacity, ld cost, int index) :
    from(from), to(to), capacity(capacity), cost(cost), index(index), flow(0) {}
};

struct SSP {
  vector<vector<Edge> > edges;
  vector<ld> pi;

  vector<Edge *>  dad;
  vector<bool> used;
  vector<ld>   dist;

  SSP(int N) : edges(N), pi(N), dad(N), used(N), dist(N) {}

  void addEdge(int from, int to, ll capacity, ld cost) {
    if(from >= edges.size() || to >= edges.size()) return;
    edges[from].PB(Edge(from, to,   capacity, cost,  edges[to].size()));
    if(from == to) ++edges[from].back().index;
    edges[to].  PB(Edge(to,   from, 0,        -cost, edges[from].size()-1));
  }

  void bellmanFord(int s) { 
    fill(pi.begin(), pi.end(), INF_ld); 
    pi[s] = 0;
    for(uint j = 0; j < edges.size(); ++j) { 
      for(auto nodeEdges : edges) {
        for(auto edge : nodeEdges) { 
          if(edge.capacity > 0) { 
            pi[edge.to] = min(pi[edge.to], pi[edge.from]+edge.cost);
          } 
        } 
      } 
    } 
  }

  pair<ll, ld> findShortestPath(int s, int t) {
    fill(dad.begin(), dad.end(), (Edge *)NULL);
    fill(used.begin(), used.end(), false);
    fill(dist.begin(), dist.end(), INF_ld);
    priority_queue<pair<ld, int> > q;
    q.push(MP(0, s));
    dist[s] = 0;
    while(!q.empty()) {
      int node = q.top().second;
      q.pop();
      if(used[node]) continue;
      used[node] = true;

      for(Edge &edge : edges[node]) {
        if(used[edge.to] || edge.capacity - edge.flow == 0) continue;

        ld tmp = dist[edge.from] + edge.cost + pi[edge.from] - pi[edge.to];
        if(tmp < dist[edge.to]) {
          dist[edge.to] = tmp;
          dad[edge.to]  = &edge;
          q.push(MP(-tmp, edge.to));
        }
      }
    }
    if(!used[t]) return MP(0, 0);

    for(uint i = 0; i < edges.size(); ++i) {
      pi[i] = min(dist[i]+pi[i], INF_ld);
    }

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
    bellmanFord(s);
    while(true) {
      pair<ll, ld> path = findShortestPath(s, t);
      if(path.first == 0) break;
      maxF += path.first;
      minC += path.second;
    }

    return MP(maxF, minC);
  }
};

int main() {
  return 0;
}