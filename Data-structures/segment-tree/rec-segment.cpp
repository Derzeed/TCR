#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;

int approxTwo(int n) {
  n = n - 1;
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4
;  n |= n >> 8;
  n |= n >> 16;
  return n + 1;
}

struct SegmentTree {
  vi tree;
  vi lazy;
  int N;

  SegmentTree(vi &values) {
    N = approxTwo(values.size());
    cout << N <<endl;
    tree.resize(N << 1, 0);
    lazy.resize(N, 0);

    for(int i = 0; i < values.size(); ++i) {
      tree[N+i] = values[i];
    }

    build(1, 0, N-1);
  }

  void build(int pos, int l, int r) {
    if(l == r) return;

    int mid = (l + r)/2;
    build(pos<<1,   l,     mid); 
    build(pos<<1|1, mid+1, r);
    tree[pos] = merge(tree[pos<<1], tree[pos<<1|1]);
  }

  void apply(int pos, int l, int r, int value) {
    tree[pos] += value*(r - l + 1);
    if(l != r) {
      lazy[pos] += value;
    }
  }

  int merge(int left, int right) {
    return left + right;
  }

  void split(int pos, int l, int r) {
    if(l == r) return;
    int mid = (l + r)/2;
    apply(pos<<1,   l,     mid, lazy[pos]);
    apply(pos<<1|1, mid+1, r,   lazy[pos]);
    lazy[pos] = 0;
  }

  void updateRec(int pos, int l, int r, int ul, int ur, int v) {
    if(ur < l || ul > r) return;
    if(ul <= l && r <= ur) return apply(pos, l, r, v);

    int mid = (l + r)/2;
    split(pos, l, r);
    updateRec(pos<<1,   l,     mid, ul, ur, v);
    updateRec(pos<<1|1, mid+1, r,   ul, ur, v);
    tree[pos] = merge(tree[pos<<1], tree[pos<<1|1]);
  }

  void update(int left, int right, int value) {
    updateRec(1, 0, N-1, left, right, value);
  }

  int queryRec(int pos, int l, int r, int ql, int qr) {
    if(qr < l || ql > r) return 0;
    if(ql <= l && r <= qr) return tree[pos];

    int mid   = (l + r)/2;
    split(pos, l, r);
    int left  = queryRec(pos<<1,   l,     mid, ql, qr);
    int right = queryRec(pos<<1|1, mid+1, r,   ql, qr);
    return merge(left, right);
  }

  int query(int l, int r) {
    return queryRec(1, 0, N-1, l, r);
  }
};

int main() {
  vi test({1, 2, 3, 4, 5, 6, 7,8,9});
  SegmentTree tree(test);

  tree.update(1, 3, 2);

  cout << tree.query(2, 2) << endl;
  return 0;
}