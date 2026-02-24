#include <cmath>
#include <cstdlib>

struct Node {
  int val;
  int depth;
  Node* parent;
  Node* left_son;
  Node* right_son;
};

class AVL {
  Node* root_;

  static bool HasChildren(Node* node) {
    return ((node->left_son != nullptr) && (node->right_son != nullptr));
  }

  enum Children { LeftSon, RightSon, Root };

  static Children TypeOfNode(Node* node) {
    if (node->parent == nullptr) {
      return Children::Root;
    }
    if (node->parent->left_son == node) {
      return Children::LeftSon;
    }
    return Children::RightSon;
  }

  static int CountBalance(Node* node) {
    int left_depth = node->left_son != nullptr ? node->left_son->depth : 0;
    int right_depth = node->right_son != nullptr ? node->right_son->depth : 0;

    return left_depth - right_depth;
  }

  // Принимает самую верхню часть поддерева, которое надо провернуть
  //  возращает самую верхню ноду после поворота
  static Node* LeftRotation(Node* node) {
    Node* b = node->right_son;

    node->right_son = b->left_son;
    b->left_son->parent = node;

    b->parent = node->parent;
    b->left_son = node;
    node->parent = b;
    return b;
  }

  // Осуществляет правый поворот аналогично LeftRotation
  static Node* RightRotation(Node* node) {
    Node* b = node->left_son;

    node->left_son = b->right_son;
    b->right_son->parent = node;

    b->parent = node->parent;
    b->right_son = node;
    node->parent = b;
    return b;
  }

  void BalanceTree(Node* node) {
    while (node != nullptr) {
      int balance = CountBalance(node);
      if (balance == -2) {
        int left_balance = CountBalance(node->left_son);
        if (left_balance == -1 || left_balance == 0) {
          node = RightRotation(node);
        } else {
          LeftRotation(node->left_son);
          node = RightRotation(node);
        }
      } else if (balance == 2) {
        int right_balance = CountBalance(node->right_son);
        if (right_balance == 1 || right_balance == 0) {
          node = LeftRotation(node);
        } else {
          RightRotation(node->right_son);
          node = LeftRotation(node);
        }
      }
      Node* node_parent = node->parent;
      if (TypeOfNode(node) == LeftSon) {
        node_parent->left_son = node;
      } else {
        node_parent->right_son = node;
      }

      if (TypeOfNode(node) == Root) {
        root_ = node;
      }
      node = node->parent;
    }
  }

 public:
  // Возвращает поинтер, где лежит x, либо поинтер на родителя того, где в
  // теории должен был лежать x
  Node* Find(int x) {
    Node* node = root_;
    while (node != nullptr) {
      if (node->val == x) {
        break;
      }

      Node* next_node;
      if (node->val > x) {
        next_node = node->left_son;
      } else {
        next_node = node->right_son;
      }

      if (next_node == nullptr) {
        break;
      }
      node = next_node;
    }

    return node;
  }

  void Insert(int x) {
    Node* node = Find(x);
    if (node->val == x) {
      return;
    }

    Node* new_node = new Node();
    new_node->val = x;
    new_node->depth = 1;
    if (node->val < x) {
      node->right_son = new_node;
    } else {
      node->left_son = new_node;
    }

    BalanceTree(node);
  }

  int LowerBound(int x) {
    Node* node = Find(x);
    if (node->val == x) {
      return x;
    }

    while (TypeOfNode(node) == RightSon) {
      node = node->parent;
    }

    if (TypeOfNode(node) == LeftSon) {
      return node->val;
    }
    return -1;
  }
};