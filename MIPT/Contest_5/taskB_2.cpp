#include <iostream>
#include <string>

struct Node {
  int val;
  Node* parent;
  Node* left_son;
  Node* right_son;
  int subtree_size;
  Node(int v)
      : val(v),
        parent(nullptr),
        left_son(nullptr),
        right_son(nullptr),
        subtree_size(1) {}

  Node* GreatParent() const {
    if (parent == nullptr) {
      return nullptr;
    }
    if (parent->parent == nullptr) {
      return nullptr;
    }
    return parent->parent;
  }
};

class SplayTree {
 private:
  Node* root_;

  static void RotateLeft(Node* x) {
    Node* y = x->right_son;
    x->right_son = y->left_son;
    if (y->left_son != nullptr) {
      y->left_son->parent = x;
    }

    y->parent = x->parent;
    if (x->parent != nullptr) {
      if (x->parent->left_son == x) {
        x->parent->left_son = y;
      } else {
        x->parent->right_son = y;
      }
    }

    y->left_son = x;
    x->parent = y;

    Update(x);
    Update(y);
  }

  static void RotateRight(Node* x) {
    Node* y = x->left_son;
    x->left_son = y->right_son;
    if (y->right_son != nullptr) {
      y->right_son->parent = x;
    }

    y->parent = x->parent;
    if (x->parent != nullptr) {
      if (x->parent->left_son == x) {
        x->parent->left_son = y;
      } else {
        x->parent->right_son = y;
      }
    }

    y->right_son = x;
    x->parent = y;

    Update(x);
    Update(y);
  }

  static void DeleteSubtree(Node* v) {
    if (v == nullptr) {
      return;
    }
    DeleteSubtree(v->left_son);
    DeleteSubtree(v->right_son);
    delete v;
  }

  void Splay(Node* v) {
    while (v->parent != nullptr) {
      Node* p = v->parent;
      Node* g = p->parent;
      if (g == nullptr) {  // zig
        if (v == p->left_son) {
          RotateRight(p);
        } else {
          RotateLeft(p);
        }
      } else if (v == p->left_son && p == g->left_son) {  // zig-zig
        RotateRight(g);
        RotateRight(p);
      } else if (v == p->right_son && p == g->right_son) {  // zig-zig
        RotateLeft(g);
        RotateLeft(p);
      } else if (v == p->right_son && p == g->left_son) {  // zig-zag
        RotateLeft(p);
        RotateRight(g);
      } else {  // zig-zag
        RotateRight(p);
        RotateLeft(g);
      }
    }
    root_ = v;
    Update(root_);
  }

  static int GetSize(Node* v) { return (v != nullptr) ? v->subtree_size : 0; }

  static void Update(Node* v) {
    if (v == nullptr) {
      return;
    }
    v->subtree_size = 1 + GetSize(v->left_son) + GetSize(v->right_son);
  }

 public:
  ~SplayTree() { DeleteSubtree(root_); }

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
      Splay(node);
      return;
    }

    Node* new_node = new Node(x);
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

    Splay(new_node);
  }

  void PrintInOrder(Node* node) {
    if (node == nullptr) {
      return;
    }
    PrintInOrder(node->left_son);
    std::cout << node->val;
    PrintInOrder(node->right_son);
  }
  void PrintTree() {
    PrintInOrder(root_);
    std::cout << '\n';
  }

  Node* GetRoot() { return root_; }

  bool Exists(int x) {
    Node* node = Find(x);
    if (node == nullptr) {
      return false;
    }
    Splay(node);
    return (node->val == x);
  }

  int Next(int x) {
    Node* cur = root_;
    Node* ans = nullptr;
    while (cur != nullptr) {
      if (cur->val > x) {
        ans = cur;
        cur = cur->left_son;
      } else {
        cur = cur->right_son;
      }
    }
    if (ans == nullptr) {
      return -1;
    }

    Splay(ans);
    return ans->val;
  }

  int Prev(int x) {
    Node* cur = root_;
    Node* ans = nullptr;
    while (cur != nullptr) {
      if (cur->val < x) {
        ans = cur;
        cur = cur->right_son;
      } else {
        cur = cur->left_son;
      }
    }
    if (ans == nullptr) {
      return -1;
    }

    Splay(ans);
    return ans->val;
  }

  Node* Kth(int k) {
    Node* v = root_;
    while (v != nullptr) {
      int left_size = GetSize(v->left_son);

      if (k == left_size + 1) {
        Splay(v);
        return v;
      }
      if (k <= left_size) {
        v = v->left_son;
      } else {
        k -= left_size + 1;
        v = v->right_son;
      }
    }
    return nullptr;  // если k неверное
  }

  void Delete(int x) {
    if (root_ == nullptr) {
      return;
    }

    Node* v = Find(x);
    Splay(v);

    if (root_->val != x) {
      return;
    }

    Node* l = root_->left_son;
    Node* r = root_->right_son;

    delete root_;

    if (l == nullptr) {
      if (r != nullptr) {
        r->parent = nullptr;
      }
      root_ = r;
      return;
    }

    l->parent = nullptr;
    root_ = l;

    Node* cur = root_;
    while (cur->right_son != nullptr) {
      cur = cur->right_son;
    }
    Splay(cur);

    root_->right_son = r;
    if (r != nullptr) {
      r->parent = root_;
    }

    Update(root_);
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cout << std::boolalpha;
  SplayTree splay = SplayTree();

  std::string operation;
  int x{};
  while (std::cin >> operation >> x) {
    if (operation == "insert") {
      splay.Insert(x);
    }
    if (operation == "delete") {
      splay.Delete(x);
    }
    if (operation == "exists") {
      std::cout << splay.Exists(x) << "\n";
    }
    if (operation == "next") {
      int result = splay.Next(x);
      if (result == -1) {
        std::cout << "none";
      } else {
        std::cout << result;
      }
      std::cout << "\n";
    }
    if (operation == "prev") {
      int result = splay.Prev(x);
      if (result == -1) {
        std::cout << "none";
      } else {
        std::cout << result;
      }
      std::cout << "\n";
    }
    if (operation == "kth") {
      Node* k_pointer = splay.Kth(x + 1);
      if (k_pointer == nullptr) {
        std::cout << "none";
      } else {
        std::cout << k_pointer->val;
      }
      std::cout << "\n";
    }
    // std::cout << "root " << splay.GetRoot()->val << "\n";
    // splay.PrintTree();
  }
}