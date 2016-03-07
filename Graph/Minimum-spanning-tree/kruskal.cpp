#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

typedef vector<int> vi;

struct DisjointSet {
  vi p;
  DisjointSet(int size) {
    for(int i = 0; i < size; ++i) p.push_back(i);
  }

  int find(int x) {
    if(x == p[x]) {
      return x;
    } else {
      return p[x] = find(p[x]);
    }
  }

  void merge(int x, int y) {
    p[find(x)] = find(y);
  }
};

//            length, from, to
typedef tuple<int,    int,  int> Edge;
typedef vector<Edge> ve;
typedef vector<ve> vve;

int Kruskal(vve vertices, ve &tree) {
  DisjointSet set(vertices.size());
  priority_queue<Edge> que;
  for(auto edges : vertices) {
    for(auto edge : edges) {
      que.push(edge);
    }
  }

  int res = 0;
  while(!que.empty()) {
    Edge edge = que.top();
    que.pop();
    if(set.find(get<1>(edge)) != set.find(get<2>(edge))) {
      set.merge(get<1>(edge), get<2>(edge));
      tree.push_back(edge);
      res += get<0>(edge);
    }
  }
  return res;
}

int main() {
  return 0;
}