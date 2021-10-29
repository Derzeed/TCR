#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

ll INF = 1L << 61;

// Takes a n*n dist vector where dist[i][j] is the distance from i to j. If no edge is connecting i to j then set dist[i][j] = INF
void floydWarshall(vvll &dist) {
  int n = dist.size();
  for(int k = 0; k < n; ++k) {
    for(int i = 0; i < n; ++i) {
      for(int j = 0; j < n; ++j) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
}

int main() {
  return 0;
}
