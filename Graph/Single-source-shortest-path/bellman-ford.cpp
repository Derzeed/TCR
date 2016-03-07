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

int INF = 1 << 29;

vi BellmanFord(vve vertices, int source) {
  vi dist(vertices.size(), INF);
  dist[source] = 0;

  for(int k = 0; k < vertices.size(); ++k) {
    for(int i = 0; i < vertices.size(); ++i) {
      for(auto edge : vertices[i]) {
        if(dist[get<1>(edge)] + get<0>(edge) < dist[get<2>(edge)]) {
          dist[get<2>(edge)] = dist[get<1>(edge)] + get<0>(edge);
        }
      }
    }
  }

  for(int i = 0; i < vertices.size(); ++i) {
    for(auto edge : vertices[i]) {
      if(dist[get<1>(edge)] + get<0>(edge) < dist[get<2>(edge)]) {
        throw("There is a negative cycle!");
      }
    }
  }

  return dist;
}

int main() {
  return 0;
}