//            length, from, to
typedef tuple<ll,     int,  int> Edge;
typedef vector<Edge> ve;
typedef vector<ve> vve;

ll INF = 1L << 61;

vll BellmanFord(vve vertices, int source) {
  vll dist(vertices.size(), INF);
  dist[source] = 0;

  for(int k = 0; k < (int) vertices.size(); ++k) {
    for(int i = 0; i < (int) vertices.size(); ++i) {
      for(auto edge : vertices[i]) {
        if(dist[get<1>(edge)] + get<0>(edge) < dist[get<2>(edge)]) {
          dist[get<2>(edge)] = dist[get<1>(edge)] + get<0>(edge);
        }
      }
    }
  }

  for(int i = 0; i < (int) vertices.size(); ++i) {
    for(auto edge : vertices[i]) {
      if(dist[get<1>(edge)] + get<0>(edge) < dist[get<2>(edge)]) {
        throw("There is a negative cycle!"); // return vll();  /* When a negative cycle is to be detected in the task */
      }
    }
  }

  return dist;
}

int main() {
  return 0;
}
