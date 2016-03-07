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

int main() {
  SCC test(3);

  test.addEdge(0,1);
  test.addEdge(0,2);
  test.addEdge(2,1);

  // test.addEdge(0, 1);
  // test.addEdge(0, 5);
  // test.addEdge(2, 0);
  // test.addEdge(2, 3);
  // test.addEdge(3, 2);
  // test.addEdge(3, 5);
  // test.addEdge(4, 2);
  // test.addEdge(4, 3);
  // test.addEdge(5, 4);

  // test.addEdge(6, 0);
  // test.addEdge(6, 4);
  // test.addEdge(6, 9);

  // test.addEdge(7, 6);
  // test.addEdge(7, 8);
  // test.addEdge(8, 7);
  // test.addEdge(8, 9);

  // test.addEdge(9, 10);
  // test.addEdge(9, 11);
  // test.addEdge(10, 12);
  // test.addEdge(11, 4);
  // test.addEdge(11, 12);
  // test.addEdge(12, 9);

  test.calcComponents();

  for(auto comp : test.components) {
    for(int v : comp) {
      cout << v << " " << test.component[v] << endl;
    }
    cout << endl;
  }

  // for(int i = 0; i < 13; ++i) {
  //   cout << i << " " << test.component[i] << endl;
  // }
  return 0;
}