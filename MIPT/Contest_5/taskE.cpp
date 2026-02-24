#include <iostream>
#include <vector>

struct Section {
  int l{};
  int r{};
  long long sql{};

  Section(int l1, int r1) : l(l1), r(r1) { sql = (r1 - l1) * (r1 - l1); };
  Section() : l(0), r(0), sql(0) {};
};

inline bool operator==(const Section& a, const Section& b) {
  return a.l == b.l && a.r == b.r;
}

inline bool operator!=(const Section& a, const Section& b) { return !(a == b); }

inline bool operator<(const Section& a, const Section& b) { return a.r <= b.l; }

inline std::ostream& operator<<(std::ostream& os, const Section& a) {
  return os << '[' << a.l << "; " << a.r << ']';
}

struct Node {
  Section val;
  int depth;  // высота поддерева, 0 для пустого
  long long acc_length;
  int size;
  Node* parent;
  Node* left_son;
  Node* right_son;
  Node(Section x)
      : val(x.l, x.r),
        depth(1),
        size(1),
        parent(nullptr),
        left_son(nullptr),
        right_son(nullptr) {
    acc_length = val.sql;
  }
};

class AVL {
  Node* root_;

  static int NodeDepth(Node* node) {
    return (node != nullptr) ? node->depth : 0;
  }

  static int NodeSqLength(Node* node) {
    return (node != nullptr) ? node->acc_length : 0;
  }

  static int SubtreeSize(Node* node) {
    return (node != nullptr) ? node->size : 0;
  }

  static void UpdateSubtreeSize(Node* node) {
    if (node == nullptr) {
      return;
    }
    node->size = 1 + SubtreeSize(node->left_son) + SubtreeSize(node->right_son);
  }

  static void UpdateSqLength(Node* node) {
    if (node == nullptr) {
      return;
    }
    node->acc_length = node->val.sql + NodeSqLength(node->left_son) +
                       NodeSqLength(node->right_son);
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

  static void UpdateNode(Node* node) {
    UpdateSqLength(node);
    UpdateSumDepth(node);
    UpdateSubtreeSize(node);
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

    UpdateNode(node);
    UpdateNode(b);

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

    UpdateNode(node);
    UpdateNode(b);

    return b;
  }

  void BalanceTree(Node* node) {
    while (node != nullptr) {
      UpdateNode(node);

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
  int GetSumLen() { return root_ != nullptr ? root_->acc_length : 0; }

  AVL() : root_(nullptr) {}

  ~AVL() {
    DeleteSubtree(root_);
    root_ = nullptr;
  }

  // Возвращает указатель на узел с val == x, либо nullptr если дерево пустое,
  // либо указатель на родителя, где мог бы лежать x (последний посещённый узел)
  Node* Find(Section x) {
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

  void Insert(Section x) {
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

  void Delete(Section x) {
    if (root_ == nullptr) {
      return;
    }
    Node* node = Find(x);
    if (node == nullptr) {
      return;
    }

    if (node->depth == 1) {  // Случай когда нет детей
      Node* parent = node->parent;
      if (parent == nullptr) {
        // удаляем корень
        delete node;
        root_ = nullptr;
        return;
      }

      if (parent->left_son == node) {
        parent->left_son = nullptr;
      } else {
        parent->right_son = nullptr;
      }

      delete node;
      BalanceTree(parent);

      return;
    }

    if (node->left_son != nullptr xor
        node->right_son != nullptr) {  // Случай когда 1 ребенок
      Node* parent = node->parent;
      Node* son = node->left_son != nullptr ? node->left_son : node->right_son;

      if (parent == nullptr) {
        root_ = son;
      } else if (parent->left_son == node) {
        parent->left_son = son;
      } else {
        parent->right_son = son;
      }
      if (son != nullptr) {
        son->parent = parent;
      }
      delete node;
      BalanceTree(parent);
      return;
    }

    Node* max_left = node->left_son;
    while (max_left->right_son != nullptr) {
      max_left = max_left->right_son;
    }
    node->val = max_left->val;
    Node* max_left_parent = max_left->parent;
    Node* repl = max_left->left_son;  // у max_left нет правого
    if (max_left_parent->left_son == max_left) {
      max_left_parent->left_son = repl;
    } else {
      max_left_parent->right_son = repl;
    }
    if (repl != nullptr) {
      repl->parent = max_left_parent;
    }

    delete max_left;
    BalanceTree(max_left_parent);
  }

  Node* Kth(int x) const {
    Node* v = root_;
    while (v != nullptr) {
      int left_size = SubtreeSize(v->left_son);
      if (x == left_size) {
        return v;  // нашли x-ую вершину
      }
      if (x <= left_size) {
        v = v->left_son;  // ищем в левом поддереве
      } else {
        x -= left_size + 1;  // пропускаем левое + текущую
        v = v->right_son;    // идём вправо
      }
    }
    return nullptr;  // если x вне диапазона [1; root_->size]
  }

  // Эту штуку буду использовать для отладки
  void PrintInOrder(Node* node) {
    if (node == nullptr) {
      return;
    }
    PrintInOrder(node->left_son);
    std::cout << node->val << "(" << node->depth << " " << node->acc_length
              << " " << node->size << ") ";
    PrintInOrder(node->right_son);
  }
  void PrintTree() {
    PrintInOrder(root_);
    std::cout << '\n';
  }

  void Divide(int x) {
    Node* node = Kth(x);
    if (node == nullptr) {
      return;
    }  // x вне диапазона

    int l = node->val.l;
    int r = node->val.r;
    if (r <= l) {
      return;
    }  // нечего делить

    int border = l + ((r - l) / 2);

    Section s1(l, border);
    Section s2(border, r);

    Delete(node->val);  // либо Delete(node) при наличии такой функции
    Insert(s1);
    Insert(s2);
  }

  void Distribute(int x) {
    Node* node = Kth(x);
    if (node == nullptr) {
      return;
    }

    Node* pref = Kth(x - 1);
    Node* next = Kth(x + 1);

    if (pref == nullptr && next == nullptr) {
      Delete(node->val);
      return;
    }

    if (next == nullptr) {
      Section s = Section(pref->val.l, node->val.r);
      Delete(node->val);
      Delete(pref->val);
      Insert(s);
      return;
    }

    if (pref == nullptr) {
      Section s = Section(node->val.l, next->val.r);
      Delete(node->val);
      Delete(next->val);
      Insert(s);
      return;
    }

    int l = node->val.l;
    int r = node->val.r;
    if (r <= l) {
      return;
    }  // нечего делить

    int border = l + ((r - l) / 2);

    Section s1(pref->val.l, border);
    Section s2(border, next->val.r);

    Delete(pref->val);
    Delete(node->val);
    Delete(next->val);

    Insert(s1);
    Insert(s2);
  }
};

int main() {
  int n{};
  std::cin >> n;
  AVL avl = AVL();
  std::vector<Section> sections(n);

  int l = 1;
  int length = 0;
  for (int i{}; i < n; i++) {
    std::cin >> length;
    sections[i].l = l;
    sections[i].r = l + length;
    avl.Insert(sections[i]);

    l += length;
  }
  //   avl.PrintTree();
  std::cout << avl.GetSumLen() << "\n";

  int q{};
  std::cin >> q;
  for (int i{}; i < q; i++) {
    int op{};
    int x{};
    std::cin >> op >> x;
    x--;
    if (op == 1) {
      avl.Distribute(x);
    } else {
      avl.Divide(x);
    }

    avl.PrintTree();
    std::cout << avl.GetSumLen() << "\n";
  }
}