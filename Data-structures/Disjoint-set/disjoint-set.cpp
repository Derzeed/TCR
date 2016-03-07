#include <cstdio>
#include <iostream>
#include <vector>

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



int main() {
  return 0;
}