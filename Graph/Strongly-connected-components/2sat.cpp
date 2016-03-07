#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

struct SCC {
  vvi edges;

  int count;
  vi index;
  vi component;
  vector<bool> onStack;
  vvi components;
  vi stack;
  int max_v;

  SCC(int max_v) : max_v(max_v), edges(max_v), index(max_v, -1), component(max_v, -1), onStack(max_v, 0) {}

  void addEdge(int from, int to) {
    edges[from].push_back(to);
  }

  void dfs(int v) {
    if(index[v] != -1) return;

    index[v] = component[v] = count++;
    onStack[v] = true;
    stack.push_back(v);

    for(int w : edges[v]) {
      dfs(w);
      if(onStack[w] == true) {
        component[v] = min(component[v], component[w]);
      }
    }

    if(component[v] == index[v]) {
      components.push_back(vi(0));
      int w;
      do {
        w = stack.back();
        stack.pop_back();
        onStack[w] = false;
        component[w] = component[v];
        components.back().push_back(w);
      } while(w != v);
    }
  }

  void calcComponents() {
    count = 0;
    components.resize(0);

    for(int v = 0; v < max_v; ++v) {
      onStack[v] = false;
      index[v] = component[v] =  -1;
    }

    for(int v = 0; v < max_v; ++v) {
      dfs(v);
    }
  }
};

struct TwoSat {
  SCC graph;
  int vars;

  TwoSat(int vars) : vars(vars), graph(2*vars) {}

  // 2*n for var_n and 2*n+1 for neg var_n
  void addClause(int fst, int scd) {
    graph.addEdge(fst^1, scd);
    graph.addEdge(scd^1, fst);
  }

  bool isSatisfiable() {
    graph.calcComponents();
    for(int i = 0; i < vars; ++i) {
      if(graph.component[2*i] == graph.component[2*i+1]) return false;
    }
    return true;
  }

  // Assumes that isSatisfiable has been called and returned true
  vector<int> getSat() {
    vector<int> sat(vars, -1);
    for(auto comp : graph.components) {
      if(sat[comp.front()>>1] != -1) continue;
      for(auto v : comp) {
        sat[v>>1] = !(v & 1);
      }
    }
    return sat;
  }
};

int main() {
  TwoSat test(3);

  test.addClause(1, 2);
  test.addClause(2, 5);
  test.addClause(5, 1);

  cout << test.isSatisfiable() << endl;

  for(auto val : test.getSat()) cout << val << endl;

  return 0;
}