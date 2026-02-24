#include <cstdlib>
#include <ctime>
#include <iostream>
#include <utility>
#include <vector>

struct Node {
  int key;       // значение элемента (a[i])
  int priority;  // приоритет для кучи
  int size;      // размер поддерева (неявный ключ)
  Node* left;
  Node* right;
  Node* parent;

  Node(int x)
      : key(x),
        priority(rand()),
        size(1),
        left(nullptr),
        right(nullptr),
        parent(nullptr) {}
  Node()
      : key(0),
        priority(rand()),
        size(0),
        left(nullptr),
        right(nullptr),
        parent(nullptr) {}
};

using TreapPair = std::pair<Node*, Node*>;

int GetSize(Node* t) { return t != nullptr ? t->size : 0; }

void UpdateSize(Node* t) {
  if (t != nullptr) {
    t->size = 1 + GetSize(t->left) + GetSize(t->right);
  }
}

TreapPair SplitByOrder(Node* p, int k) {
  if (p == nullptr) {
    return TreapPair(nullptr, nullptr);
  }
  if (GetSize(p->left) + 1 <= k) {
    TreapPair q = SplitByOrder(p->right, k - GetSize(p->left) - 1);
    p->right = q.first;
    UpdateSize(p);
    return TreapPair(p, q.second);
  }

  TreapPair q = SplitByOrder(p->left, k);
  p->left = q.second;
  UpdateSize(p);
  return TreapPair(q.first, p);
}

TreapPair SplitByValue(Node* p, int x) {
  if (p == nullptr) {
    return TreapPair(nullptr, nullptr);
  }

  if (p->key <= x) {
    TreapPair q = SplitByValue(p->right, x);
    p->right = q.first;
    UpdateSize(p);
    return TreapPair(p, q.second);
  }

  TreapPair q = SplitByOrder(p->left, x);
  p->left = q.second;
  UpdateSize(p);
  return TreapPair(q.first, p);
}

Node* Merge(Node* l, Node* r) {
  if (l == nullptr || r == nullptr) {
    return l != nullptr ? l : r;
  }

  if (l->priority > r->priority) {
    l->right = Merge(l->right, r);
    UpdateSize(l);
    return l;
  }
  r->left = Merge(l, r->left);
  UpdateSize(r);
  return r;
}