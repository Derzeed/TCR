#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

int LCS(vi x, vi y, vvi &c) {
  c = vvi(x.size()+1, vi(y.size()+1, 0));
  for(int i = 1; i <= x.size(); ++i) {
    for(int j = 1; j <= y.size(); ++j) {
      if(x[i] == y[j]) {
        c[i][j] = c[i-1][j-1] + 1;
      } else {
        c[i][j] = max(c[i][j-1], c[i-1][j]);
      }
    }
  }
  return c[x.size()][y.size()];
}

vi recreateSequence(vi x, vi y, vvi c) {
  int i(x.size()), y(y.size());
  vi res;
  while(i != 0 && j != 0) {
    if(x[i] == y[i]) {
      res.push_back(x[i]);
      --i, --j;
    } else if(c[i][j-1] > c[i-1][j]) {
      --j;
    } else {
      --i;
    }
  }
  reverse(res.begin(), res.end());
  return res;
}

int main() {
  return 0;
}