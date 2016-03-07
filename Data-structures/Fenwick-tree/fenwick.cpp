#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;

int phi(int n) { return n & -n; }

vi arr;
int N; // x[i] exists for all 1 <= i <= N

int get(int k) { // Returns x[1] + x[2] + ... + x[k]
  int sum = 0;
  for(int i = k; i >= 0; i -= phi(i)) sum += arr[i];
  return sum;
}

void add(int k, int v) { // x[k] += v
  for(int i = k; i <= N; i += phi(i)) arr[i] += v;
}

int main() {
  return 0;
}