#include <iostream>

struct Node {
  int val;
  int depth;  // высота поддерева, 0 для пустого
  Node* parent;
  Node* left_son;
  Node* right_son;
  Node(int v)
      : val(v),
        depth(1),
        parent(nullptr),
        left_son(nullptr),
        right_son(nullptr) {}
};

class AVL {
  Node* root_;

  static int NodeDepth(Node* node) {
    return (node != nullptr) ? node->depth : 0;
  }

  enum Children { LeftSon, RightSon, Root };

  static Children TypeOfNode(Node* node) {
    if (node == nullptr || node->parent == nullptr) {
      return Children::Root;
    }
    if (node->parent->left_son == node) {
      return Children::LeftSon;
    }
    return Children::RightSon;
  }

  static int CountBalance(Node* node) {
    // balance = height(left) - height(right)
    return NodeDepth(node->left_son) - NodeDepth(node->right_son);
  }

  static void UpdateSumDepth(Node* node) {
    if (node == nullptr) {
      return;
    }
    node->depth =
        1 + std::max(NodeDepth(node->left_son), NodeDepth(node->right_son));
  }

  // Левый поворот вокруг node, возвращает новый вверх (b)
  static Node* LeftRotation(Node* node) {
    Node* b = node->right_son;
    if (b == nullptr) {
      return node;
    }

    node->right_son = b->left_son;
    if (b->left_son != nullptr) {
      b->left_son->parent = node;
    }

    b->left_son = node;
    b->parent = node->parent;
    node->parent = b;

    UpdateSumDepth(node);
    UpdateSumDepth(b);

    return b;
  }

  // Правый поворот вокруг node, возвращает новый верх (b)
  static Node* RightRotation(Node* node) {
    Node* b = node->left_son;
    if (b == nullptr) {
      return node;
    }

    node->left_son = b->right_son;
    if (b->right_son != nullptr) {
      b->right_son->parent = node;
    }

    b->right_son = node;
    b->parent = node->parent;
    node->parent = b;

    UpdateSumDepth(node);
    UpdateSumDepth(b);

    return b;
  }

  void BalanceTree(Node* node) {
    while (node != nullptr) {
      UpdateSumDepth(node);

      int balance = CountBalance(node);
      Node* old_parent = node->parent;
      Node* new_top = node;

      if (balance > 1) {
        if (CountBalance(node->left_son) >= 0) {
          new_top = RightRotation(node);
        } else {
          node->left_son = LeftRotation(node->left_son);
          if (node->left_son != nullptr) {
            node->left_son->parent = node;
          }
          new_top = RightRotation(node);
        }
      } else if (balance < -1) {
        if (CountBalance(node->right_son) <= 0) {
          new_top = LeftRotation(node);
        } else {
          node->right_son = RightRotation(node->right_son);
          if (node->right_son != nullptr) {
            node->right_son->parent = node;
          }
          new_top = LeftRotation(node);
        }
      }

      if (new_top != node) {
        if (old_parent == nullptr) {
          root_ = new_top;
          new_top->parent = nullptr;
        } else {
          if (old_parent->left_son == node) {
            old_parent->left_son = new_top;
          } else {
            old_parent->right_son = new_top;
          }
          new_top->parent = old_parent;
        }
      } else {
        if (old_parent == nullptr) {
          root_ = node;
        }
      }

      node = old_parent;
    }
  }

  static void DeleteSubtree(Node* node) {
    if (node == nullptr) {
      return;
    }
    DeleteSubtree(node->left_son);
    DeleteSubtree(node->right_son);
    delete node;
  }

 public:
  AVL() : root_(nullptr) {}

  ~AVL() {
    DeleteSubtree(root_);
    root_ = nullptr;
  }

  // Возвращает указатель на узел с val == x, либо nullptr если дерево пустое,
  // либо указатель на родителя, где мог бы лежать x (последний посещённый узел)
  Node* Find(int x) {
    Node* node = root_;
    Node* last = nullptr;
    while (node != nullptr) {
      last = node;
      if (node->val == x) {
        return node;
      }
      if (x < node->val) {
        node = node->left_son;
      } else {
        node = node->right_son;
      }
    }
    return last;
  }

  void Insert(int x) {
    if (root_ == nullptr) {
      root_ = new Node(x);
      return;
    }

    Node* node = Find(x);
    if ((node != nullptr) && node->val == x) {
      return;
    }

    Node* new_node = new Node(x);
    new_node->depth = 1;
    new_node->left_son = nullptr;
    new_node->right_son = nullptr;

    if (node == nullptr) {
      root_ = new_node;
    } else if (x < node->val) {
      node->left_son = new_node;
      new_node->parent = node;
    } else {
      node->right_son = new_node;
      new_node->parent = node;
    }

    BalanceTree((new_node->parent != nullptr) ? new_node->parent : new_node);
  }

  int LowerBound(int x) {
    Node* cur = root_;
    Node* ans = nullptr;
    while (cur != nullptr) {
      if (cur->val >= x) {
        ans = cur;
        cur = cur->left_son;
      } else {
        cur = cur->right_son;
      }
    }
    return (ans != nullptr) ? ans->val : -1;
  }

  // Эту штуку буду использовать для отладки
  void PrintInOrder(Node* node) {
    if (node == nullptr) {
      return;
    }
    PrintInOrder(node->left_son);
    std::cout << node->val << "(" << node->depth << ") ";
    PrintInOrder(node->right_son);
  }
  void PrintTree() {
    PrintInOrder(root_);
    std::cout << '\n';
  }
};

int main() {
  AVL avl = AVL();
  int q{};
  const int cMod{1000000000};
  std::cin >> q;
  char operation;
  char prev_operation{' '};
  int prev_lower_bound_res = 0;
  int num;
  for (int i{}; i < q; i++) {
    std::cin >> operation >> num;

    if (operation == '?') {
      prev_lower_bound_res = avl.LowerBound(num);
      std::cout << prev_lower_bound_res << "\n";

    } else {
      if (prev_operation == '?' && prev_lower_bound_res != -1) {
        avl.Insert((num + prev_lower_bound_res) % cMod);
      } else {
        avl.Insert(num);
      }
    }

    prev_operation = operation;
  }
}