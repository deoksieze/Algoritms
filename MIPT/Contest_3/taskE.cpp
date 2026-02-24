#include <cstdlib>
#include <iostream>
#include <ostream>

struct Node {
  int elem;
  Node* next;
  Node* prev;

  Node(int e = 0, Node* n = nullptr, Node* p = nullptr)
      : elem(e), next(n), prev(p) {}
};

class LinkedList {
  Node* head_;
  Node* tail_;
  Node* center_;
  int len_{};

 public:
  LinkedList() {
    head_ = new Node;
    tail_ = new Node;

    head_->next = tail_;
    head_->prev = nullptr;
    head_->elem = -1;

    tail_->prev = head_;
    tail_->next = nullptr;
    tail_->elem = -1;

    center_ = head_;
    len_ = 0;
  }

  void PushBack(int num) {
    Node* x = new Node{num, tail_, tail_->prev};
    tail_->prev->next = x;
    tail_->prev = x;
    len_++;

    if (len_ == 1) {
      center_ = x;
    } else if (len_ % 2 != 0) {
      center_ = center_->next;
    }
  }

  void PutCenter(int num) {
    // std::cout << center_->elem << "\n";
    Node* x = new Node{num, center_, center_->next};
    center_->next->prev = x;
    center_->next = x;
    len_++;
    if (len_ % 2 != 0) {
      center_ = center_->next;
    }
  }

  int PopBegin() {
    Node* first = head_->next;
    int num = first->elem;

    head_->next = first->next;
    first->next->prev = head_;
    delete first;
    len_--;
    if (len_ == 0) {
      center_ = head_;
    } else if (len_ % 2 != 0 && center_ != head_) {
      center_ = center_->prev;
    }

    return num;
  }

  void Print() {
    Node* current = head_;
    std::cout << head_->elem << " ";
    while (current->next != 0) {
      current = current->next;
      std::cout << current->elem << " ";
    }
    std::cout << "\n";
  }

  ~LinkedList() {
    Node* cur = head_;
    while (cur != 0) {
      Node* next = cur->next;
      delete cur;
      cur = next;
    }
  }
};

int main() {
  int q{};
  std::cin >> q;
  LinkedList ll{};

  char op{};
  for (int i{}; i < q; i++) {
    std::cin >> op;
    if (op == '+') {
      int n{};
      std::cin >> n;
      ll.PushBack(n);
    }
    if (op == '*') {
      int n{};
      std::cin >> n;
      ll.PutCenter(n);
    }
    if (op == '-') {
      std::cout << ll.PopBegin() << '\n';
    }
  }
}