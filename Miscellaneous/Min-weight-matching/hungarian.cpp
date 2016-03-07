#include <cstdio>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

int INF = numeric_limits<int>::max();

int hungarian(vvi &costs, int n, int m, vi &ans) {
  vi u(n + 1, 0), v(m + 1, 0), p(m + 1, 0), way(m + 1, 0);
  for(int i = 1; i <= n; ++i) {
    p[0] = i;
    int j0 = 0;
    
    vi used(m + 1, false);
    vi minV(m + 1, INF);
    while(p[j0] != 0) {
      used[j0] = true;
      int i0 = p[j0], delta = INF, j1;
      for(int j = 1; j <= m; ++j) if(!used[j]) {
        int tmp = costs[i0-1][j-1] - u[i0] - v[j];
        if(tmp < minV[j]) {
          minV[j] = tmp;
          way[j] = j0;
        }
        if(minV[j] < delta) {
          delta = minV[j];
          j1 = j;
        }
      }

      for(int j = 0; j <= m; ++j) {
        if(used[j]) {
          u[p[j]] += delta;
          v[j] -= delta;
        } else {
          minV[j] -= delta;
        }
      }

      j0 = j1;
    }

    while(j0 != 0) {
      int j1 = way[j0];
      p[j0] = p[j1];
      j0 = j1;
    }
  }

  ans.resize(n);
  for(int i = 1; i <= m; ++i) if(p[i] != 0) {
    ans[p[i]-1] = i-1;
  }

  return -v[0];
}

int main() {
  vvi costs({
    {-10, -10, -13, -14},
    {-19, -18, -16, -17},
    {-8,  -7,  -9,  -10},
    {-15, -17, -14, -19}
  });

  vi ans;

  cout << -hungarian(costs, 4, 4, ans) << endl;

  for(auto nr : ans) cout << nr << endl;
  return 0;
}