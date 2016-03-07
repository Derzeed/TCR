#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

#define MT(args...) make_tuple(args)

using namespace std;

typedef vector<int> vi;

//            length, from, to
typedef tuple<int,    int,  int> Edge;
typedef vector<Edge> ve;
typedef vector<ve> vve;
typedef tuple<int, int> tii;

int INF = 1 << 29;

vi Dijkstra(vve vertices, int source) {
  vi dist(vertices.size(), INF);
  priority_queue<tii> que;
  que.push(MT(0, source));

  while(!que.empty()) {
    int vertex, length;
    tie(vertex, length) = que.top();
    que.pop();

    if(length < dist[vertex]) {
      dist[vertex] = length;
      for(auto edge : vertices[vertex]) {
        if(length + get<0>(edge) < dist[get<2>(edge)]) {
          que.push(MT(get<2>(edge), length + get<0>(edge)));
        }
      }
    }
  }
  return dist;
}

int main() {
  return 0;
}