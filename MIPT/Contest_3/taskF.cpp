#include <climits>
#include <iostream>
#include <ostream>
#include <stack>
#include <string>

using Llpair = std::pair<long long, long long>;

class StackWithMin {
  std::stack<Llpair> stack_;

 public:
  bool Empty() { return stack_.empty(); }

  void PushNumber(long long num) {
    long long stack_min = stack_.empty() ? num : stack_.top().second;
    Llpair pair = {num, num < stack_min ? num : stack_min};
    stack_.push(pair);
  }

  void PopBack() { stack_.pop(); }

  Llpair Top() { return stack_.top(); }

  long long GetMin() { return stack_.top().second; }

  void Clear() {
    while (!stack_.empty()) {
      stack_.pop();
    }
  }
};

class DequeWithMin {
  StackWithMin first_{};
  StackWithMin second_{};
  long long size_{};

  void MoveAllFromFirstToSecond() {
    while (!first_.Empty()) {
      Llpair pair = first_.Top();
      second_.PushNumber(pair.first);
      first_.PopBack();
    }
  }

 public:
  void Enqueue(long long num) {
    first_.PushNumber(num);
    size_++;
    std::cout << "ok" << '\n';
  }

  void Dequeue() {
    if (second_.Empty() && first_.Empty()) {
      std::cout << "error" << '\n';
      return;
    }

    if (second_.Empty()) {
      MoveAllFromFirstToSecond();
    }

    std::cout << second_.Top().first << '\n';
    second_.PopBack();
    size_--;
  }

  void Front() {
    if (second_.Empty() && first_.Empty()) {
      std::cout << "error" << '\n';
      return;
    }

    if (second_.Empty()) {
      MoveAllFromFirstToSecond();
    }

    std::cout << second_.Top().first << '\n';
  }

  void Size() const { std::cout << size_ << '\n'; }

  void Clear() {
    second_.Clear();
    first_.Clear();
    size_ = 0;
    std::cout << "ok\n";
  }

  void Min() {
    if (second_.Empty() && first_.Empty()) {
      std::cout << "error" << '\n';
      return;
    }

    long long current_min = LLONG_MAX;
    if (first_.Empty() || second_.Empty()) {
      current_min = first_.Empty() ? second_.Top().second : first_.Top().second;
    } else {
      current_min = first_.GetMin() < second_.GetMin() ? first_.GetMin()
                                                       : second_.GetMin();
    }
    std::cout << current_min << '\n';
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n{};
  std::cin >> n;
  std::string str{};
  DequeWithMin dwm{};

  for (int i{}; i < n; i++) {
    std::cin >> str;
    if (str == "enqueue") {
      long long num{};
      std::cin >> num;
      dwm.Enqueue(num);
    } else if (str == "front") {
      dwm.Front();
    } else if (str == "dequeue") {
      dwm.Dequeue();
    } else if (str == "size") {
      dwm.Size();
    } else if (str == "clear") {
      dwm.Clear();
    } else if (str == "min") {
      dwm.Min();
    }
  }
}