#include <deque>
#include <iostream>

// Будем поддерживать инвариант, что первой половине не меньше элементов чем во
// второй (столько же или на один больше)
class MyDeque {
  std::deque<int> first_half_;
  std::deque<int> second_half_;

 public:
  void Print() {
    std::cout << "First half: ";
    for (auto i : first_half_) {
      std::cout << i << " ";
    }

    std::cout << "\nSecond half: ";
    for (auto i : second_half_) {
      std::cout << i << " ";
    }

    std::cout << std::endl;
  }

  void PushBack(int num) {
    second_half_.push_back(num);
    if (second_half_.size() > first_half_.size()) {
      int x = second_half_[0];
      second_half_.pop_front();
      first_half_.push_back(x);
    }
  }

  void PushCenter(int num) {
    if (first_half_.size() > second_half_.size()) {
      second_half_.push_front(num);
    } else {
      first_half_.push_back(num);
    }
  }

  int PopBegin() {
    int num = first_half_[0];
    first_half_.pop_front();
    if (first_half_.size() < second_half_.size()) {
      int temp = second_half_[0];
      second_half_.pop_front();
      first_half_.push_back(temp);
    }
    return num;
  }
};

int main() {
  int n{};
  std::cin >> n;

  MyDeque deck{};
  for (int i{}; i < n; i++) {
    char q{};
    std::cin >> q;
    if (q == '+') {
      int num{};
      std::cin >> num;
      deck.PushBack(num);
    } else if (q == '*') {
      int num{};
      std::cin >> num;
      deck.PushCenter(num);
    } else {
      std::cout << deck.PopBegin() << '\n';
    }
    // deck.Print();
  }
}