#include <cstdio>
#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

int INF = numeric_limits<int>::max();

struct HK {
  int N;
  vvi edges;
  vi pair_u, pair_v;
  vi dist;

  HK(int N, int M, vvi &edges) : N(N), pair_u(N+1, 0), pair_v(M+1, 0), dist(N+1), edges(edges) {}

  bool BFS() {
    fill(dist.begin(), dist.end(), INF);

    queue<int> q;

    for(int u = 1; u <= N; ++u) {
      if(pair_u[u] == 0) {
        dist[u] = 0;
        q.push(u);
      }
    }

    while(!q.empty()) {
      int u = q.front();
      q.pop();

      for(int v : edges[u]) {
        if(dist[pair_v[v]] == INF) {
          dist[pair_v[v]] = dist[u] + 1;
          q.push(pair_v[v]);
        }
      }
    }

    return dist[0] != INF;
  }

  bool DFS(int u) {
    if(u == 0) return true;
    for(int v : edges[u]) {
      if(dist[pair_v[v]] == dist[u] + 1) {
        if(DFS(pair_v[v])) {
          pair_v[v] = u;
          pair_u[u] = v;
          return true;
        }
      }
    }
    dist[u] = INF;
    return false;
  }

  int maxMatching() {
    int matching = 0;
    while(BFS()) {
      for(int u = 1; u <= N; ++u) {
        if(pair_u[u] == 0) {
          if(DFS(u)) {
            ++matching;
          }
        }
      }
    }
    return matching;
  }
};

int main() {
  int N, M, P;
  cin >> N >> M >> P;

  vvi edges(N+1);

  while(P --> 0) {
    int a, b;
    cin >> a >> b;
    edges[a].push_back(b);
  }

  cout << HK(N, M, edges).maxMatching() << endl;


  return 0;
}