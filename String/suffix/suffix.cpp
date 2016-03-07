#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Node {
  char ch;
  int len; 
  Node *link;
  map<int, Node*> to;
};
using pnode = Node*;

struct Suffix {
  vector<pnode> nodes;
  pnode last;

  Suffix() {
    last = new Node { -1, 0, NULL, {} };
    last->link = last;
    nodes.push_back(last);
  }

  void addLetter(char ch) {
    pnode p = last;
    last = new Node { ch, p->len+1, NULL, {} };
    nodes.push_back(last);

    for(; p->to.count(ch) == 0; p = p->link) {
      p->to[ch] = last;
    }

    pnode q = p->to[ch];
    if(q == last) {
      last->link = p;
    } else if(p->len + 1 == q->len) {
      last->link = q;
    } else {
      pnode cpy = new Node { ch, p->len+1, q->link, q->to };
      nodes.push_back(cpy);
      last->link = q->link = cpy;
      for(; p->to[ch] == q; p = p->link) {
        p->to[ch] = cpy;
      }
    }
  }
};

int main() {
  return 0;
}