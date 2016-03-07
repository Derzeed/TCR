#include <cstdio>
#include <iostream>
#include <vector>
#include <tuple>
#include <random>

#define mt(args...) make_tuple(args)

using namespace std;

typedef struct Node* pnode;
void updateNode(pnode node);
struct Node {
  int priority, key, cnt;
  pnode left, right;

  // Node() {}
  Node(int key, int priority) : key(key), priority(priority), left(NULL), right(NULL), cnt(1) {}
  Node(int key, int priority, pnode left, pnode right) 
  : key(key), priority(priority), left(left), right(right) {
    updateNode(this);
  }
};

int cnt(pnode node) {
  return (node == NULL ? 0 : node->cnt);
}

void updateNode(pnode node) {
  if(node != NULL) {
    node->cnt = 1 + cnt(node->left)  + cnt(node->right);
  }
}

bool search(pnode node, int key) {
  if(node == NULL) {
    return false;
  } else if(key == node->key) {
    return true;
  } else if(key < node->key) {
    return search(node->left, key);
  } else {
    return search(node->right, key);
  }
}

tuple<pnode, pnode> split(pnode node, int key) {
  if(node == NULL) {
    return mt((pnode)NULL, (pnode)NULL);
  } else if(key < node->key) {
    pnode left, right;
    tie(left, right) = split(node->left, key);
    return mt(left, new Node(node->key, node->priority, right, node->right));
  } else { 
    pnode left, right;
    tie(left, right) = split(node->right, key);
    return mt(new Node(node->key, node->priority, node->left, left), right);
  }
}

pnode insert(pnode node, pnode el) {
  if(node == NULL) {
    return el;
  } else if(el->priority < node->priority) {
    if(el->key < node->key) {
      return new Node(node->key, node->priority, insert(node->left, el), node->right);
    } else {
      return new Node(node->key, node->priority, node->left, insert(node->right, el));
    }
  } else {
    tie(el->left, el->right) = split(node, el->key);
    updateNode(el);
    return el;
  }
}

pnode merge(pnode left, pnode right) {
  if(left == NULL) {
    return right;
  } else if(right == NULL) {
    return left;
  } else if(left->priority > right->priority) {
    pnode node = merge(left->right, right);
    return new Node(left->key, left->priority, left->left, node);
  } else {
    pnode node = merge(left, right->left);
    return new Node(right->key, right->priority, node, right->right);
  }
}

pnode erase(pnode node, int key) {
  if(node == NULL) {
    return NULL;
  } else if(key == node->key) {
    return merge(node->left, node->right);
  } else if(key < node->key) {
    return new Node(node->key, node->priority, erase(node->left, key), node->right);
  } else {
    return new Node(node->key, node->priority, node->left, erase(node->right, key));
  }
}

pnode unite(pnode fst, pnode scd) {
  if(fst == NULL) {
    return scd;
  } else if(scd == NULL) {
    return fst;
  } else if(fst->priority < scd->priority) {
    return unite(scd, fst);
  } else {
    pnode a, b;
    tie(a, b) = split(scd, fst->key);
    return new Node(fst->key, fst->priority, unite(fst->left, a), unite(fst->right, b));
  }
}

int main() {
  random_device rd;

  // cout << rd.entropy() << endl; 

  pnode root1 = NULL;
  root1 = insert(root1, new Node(1, rd()));
  root1 = insert(root1, new Node(2, rd()));
  root1 = insert(root1, new Node(3, rd()));
  root1 = insert(root1, new Node(4, rd()));
  root1 = insert(root1, new Node(5, rd()));

  pnode root2 = NULL;
  root2 = insert(root2, new Node(3, rd()));
  cout << root2->cnt << endl;
  root2 = insert(root2, new Node(4, rd()));
  cout << root2->cnt << endl;
  root2 = insert(root2, new Node(5, rd()));
  cout << root2->cnt << endl;
  root2 = insert(root2, new Node(6, rd()));
  cout << root2->cnt << endl;
  root2 = insert(root2, new Node(7, rd()));
  cout << root2->cnt << endl;
  root2 = erase(root2, 6);
  cout << root2->cnt << endl;

  pnode un = unite(root1, root2);
  un = erase(un, 5);

  root2 = insert(root2, new Node(8, rd()));
  cout << root2->cnt << endl;
  // // // pnode intersection = intersect(root1, root2);

  cout << "root1" << endl;
  for(int i = 1; i <= 8; ++i) {
    cout << i << " " << search(root1, i) << endl;
  }
  cout << root1->cnt << endl;

  cout << "root2" << endl;
  for(int i = 1; i <= 8; ++i) {
    cout << i << " " << search(root2, i) << endl;
  }
  cout << root2->cnt << endl;

  cout << "union" << endl;
  for(int i = 1; i <= 8; ++i) {
    cout << i << " " << search(un, i) << endl;
  }
  cout << un->cnt << endl;

  // cout << "intersection" << endl;
  // for(int i = 1; i <= 7; ++i) {
  //   cout << i << " " << search(intersection, i) << endl;
  // }
  return 0;
}