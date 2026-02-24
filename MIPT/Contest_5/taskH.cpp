#include <iostream>
#include <ostream>
#include <vector>

struct Node {
  int key;
  int priority;
  Node* right;
  Node* left;
  Node* parent;
  Node(int x, int y)
      : key(x), priority(y), right(nullptr), left(nullptr), parent(nullptr) {};
};

void PrintNode(Node* t) {
  if (t != nullptr) {
    std::cout << t->key;
  } else {
    std::cout << 0;
  }
  std::cout << " ";
}

void PrintTree(Node* t) {
  if (t == nullptr) {
    return;
  }

  PrintNode(t->parent);
  PrintNode(t->left);
  PrintNode(t->right);
  std::cout << "\n";

  PrintTree(t->left);
  PrintTree(t->right);
}

void Split(Node* t, int k, Node*& l, Node*& r) {
  if (t == nullptr) {
    return;
  }
  if (k > t->key) {
    Split(t->right, k, t->right, r);
    l = t;
  } else {
    Split(t->left, k, l, t->left);
    r = t;
  }
}

Node* Merge(Node* l, Node* r) {
  if (l == nullptr || r == nullptr) {
    return l != nullptr ? l : r;
  }

  if (l->priority > r->priority) {
    l->right = Merge(l->right, r);
    return l;
  }
  r->left = Merge(l, r->left);
  return r;
}

void Insert(Node*& t, int x, int y) {
  Node node = Node(x, y);
  t = Merge(t, &node);
}