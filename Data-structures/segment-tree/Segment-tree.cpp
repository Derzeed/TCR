#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int approxTwo(int n) {
  n = n - 1;
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  n |= n >> 16;
  return n + 1;
}

struct SegmentTree {
  vi t;
  vi d;
  int N;
  int H;

  SegmentTree(vi &values) {
    N = approxTwo(values.size());
    H = 8 * sizeof(int) - __builtin_clz(N);

    t.resize(N << 1);
    d.resize(N);
    for(int i = 0; i < values.size(); ++i) {
      t[i+N] = values[i];
    }

    for(int i = N - 1; i >= 1; --i) {
      t[i] = merge(t[i<<1], t[i<<1|1]);
    }
  }

  int merge(int a, int b) { // Assymetric combiner function
    return a + b;
  }

  void apply(int p, int value, int k) {
    t[p] += value * k;
    if(p < N) d[p] += value;
  }

  void build(int p) {
    for(p >>= 1; p >= 1; p >>= 1) {
      t[p] = merge(merge(t[p<<1], t[p<<1|1]), d[p]);
    }
  }

  void push(int p) {
    int k = N; // size of segment. Can be excluded
    for(int s = H; s > 0; --s, k >>= 1) {
      int i = p >> s;
      if(d[i]) {
        apply(i<<1,   d[i], k);
        apply(i<<1|1, d[i], k);
        d[i] = 0;
      }
    }
  }

  void update(int l, int r, int value) { // update interval [l, r)
    int l0 = (l += N);
    int r0 = (r += N);
    push(l0);
    push(r0-1);
    for(int k = 1; r > l; l >>= 1, r >>= 1, k <<= 1) {
      // l is the right child of the parent, so include l but not the parent
      if(l&1) apply(l++, value, k);
      // r is the right child of the parent, so include the left child but not the parent
      if(r&1) apply(--r, value, k);
    }
    build(l0);
    build(r0-1);
  }

  int query(int l, int r) { // query interval [l, r)
    push(l+N);
    push(r+N-1);
    int res = 0;
    for(l += N, r += N; r > l; l >>= 1, r >>= 1) {
      if(l&1) res = merge(res, t[l++]);
      if(r&1) res = merge(t[--r], res);
    }
    return res;
  }
};

int main() {
  vi test({1, 2, 3, 4, 5, 6});
  SegmentTree tree(test);

  tree.update(1, 3, 2);
  cout << "Testing" << endl;
  assert(tree.query(2, 5) == 14);
  assert(tree.query(0, 2) == 5);
  cout << "Testing complete" << endl;
  return 0;
}
