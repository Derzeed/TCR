#include <iostream>
#include <cstdio>

using namespace std;

struct Node {
  int key;
  double priority;
  Node *left, *right;
};
using pnode = Node*;

void update(pnode node) {
  if(node == NULL) return;
  // Update the necessary invariants
}

void push(pnode node) {
  if(node == NULL) return;
  // Add the lazy propagation
}

void split(pnode root, int key, pnode &l, pnode &r) {
  if(root == NULL) {
    l = r = NULL;
  } else if(key < root->key) {
    push(root);
    r = root;
    split(r->left, key, l, r->left);
    update(r);
  } else {
    push(root);
    l = root;
    split(l->right, key, l->right, r);
    update(l);
  }
}

void merge(pnode &root, pnode l, pnode r) {
  if(l == NULL || r == NULL) {
    root = l != NULL ? l : r;
  } else if(l->priority > r->priority) {
    push(l);
    root = l;
    merge(root->right, l->right, r);
    update(root);
  } else {
    push(r);
    root = r;
    merge(root->left, l, r->left);
    update(root);
  }
}

void insert(pnode &root, pnode newNode) {
  if(root == NULL) {
    root = newNode;
  } else if(newNode->priority > root->priority) {
    push(root);
    split(root, newNode->key, newNode->left, newNode->right);
    root = newNode;
    update(root);
  } else if(newNode->key < root->key) {
    push(root);
    insert(root->left, newNode);
    update(root);
  } else {
    push(root);
    insert(root->right, newNode);
    update(root);
  }
}

int main() {
  return 0;
}