#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

int phi(int n) { return n & -n; }

vvi arr;
int N; // x[i][j] exists for all 1 <= i, j <= N

int get(int k, int l) { // Returns sum_{1 <= i <= k, 1 <= j <= l} x[i][j]
  int sum = 0;
  for(int i = k; i > 0; i -= phi(i))
  for(int j = l; j > 0; j -= phi(j)) 
    sum += arr[i][j];
  return sum;
}

void add(int k, int l, int v) { // x[k][l] += v
  for(int i = k; i <= N; i += phi(i))
  for(int j = l; j <= N; j += phi(j))
    arr[i][j] += v;
}

int main() {
  return 0;
}
