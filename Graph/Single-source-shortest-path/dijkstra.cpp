#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

#define MT(args...) make_tuple(args)
#define F first
#define S second
using namespace std;

typedef vector<int> vi;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;

vi Dijkstra(vvii &con, int s) {
  vi dis(con.size(), -1);
  priority_queue<ii> q;
  q.push({0, s});

  while(!q.empty()) {
    int v, d; // d is negative
    tie(v, d) = q.top();
    q.pop();
    if(dis[v] != -1) continue;
    dis[v] = -d;
    for(auto e : con[v]) {
      q.push({d-e.F, e.S});
    }
  }
  return dis;
}

int main() {
  return 0;
}
