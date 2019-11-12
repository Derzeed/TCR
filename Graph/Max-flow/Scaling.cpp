#include <bits/stdc++.h>
using namespace std;
#define PB push_back

typedef long long ll;

const ll INF = numeric_limits<ll>::max();

struct Edge {
    ll cap, base; // base is optional
    int from, to, index;
    Edge(int from, int to, ll cap, int index) : from(from), to(to), cap(cap), base(cap), index(index) {}
};

struct Scaling { //O(|E|^2*log(C_max))
    vector<vector<Edge> > edges;
    vector<int> level;
    vector<int> vis;
    ll max_cap = 0;
    Scaling(int N) : edges(N), level(N), vis(N) {}

    void addEdge(int from, int to, ll cap) {
        if(from == to) return;
        max_cap = max(max_cap,cap);
        edges[from].PB(Edge(from,to,cap,edges[to].size()));
        edges[to].PB(Edge(to,from,0,edges[from].size()-1));
    }

    ll findFlow(int node, int t, ll flow, ll limit) {
        if(node == t) return flow;
        if(vis[node]) return 0;
        vis[node] = true;
        for(Edge &edge : edges[node]) {
            if(edge.cap >= limit) {
                if(ll tmp = findFlow(edge.to,t,min(flow,edge.cap),limit)) {
                    edge.cap -= tmp;
                    edges[edge.to][edge.index].cap += tmp;
                    return tmp;
                }
            }
        }
        return 0;
    }

    ll maxFlow(int s,int t) {
        ll totFlow = 0;
        ll lim = max_cap;
        while(lim > 0) {
            ll res = 0;
            do {
               totFlow += res;
               fill(vis.begin(),vis.end(),false);
            } while(res = findFlow(s,t,INF,lim));
            lim /= 2;
        }
        return totFlow;
    }
};

int main() { //tested on https://open.kattis.com/problems/maxflow
  int N, M, s,t;

  cin >> N >> M >> s >> t;

  Scaling instance(N);
  for(int i = 0; i < M; ++i) {
    int from, to;
    ll capacity;
    cin >> from >> to >> capacity;
    instance.addEdge(from, to, capacity);
  }

  cout << N << " " << instance.maxFlow(s, t) << " ";
  int mprime = 0;
  for(auto v : instance.edges) {
    for(auto e : v) {
      if(e.base > 0 && e.cap != e.base) mprime++;
    }
  }
  cout << mprime << endl;
  for(auto v : instance.edges) {
    for(auto e : v) {
      if(e.base > 0 && e.cap != e.base) {
        cout << e.from << " " << e.to << " " << e.base-e.cap << endl;
      }
    }
  }
  return 0;
}
