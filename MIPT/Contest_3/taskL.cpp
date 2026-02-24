#include <iostream>
#include <vector>

template <typename T>
void PrintArray(std::vector<T>& i) {
  for (auto j : i) {
    std::cout << j << " ";
  }
  std::cout << "\n";
}

template <typename T>
class MaxMinHeap {
 private:
  std::vector<T> data_;

  void Swap(int i, int j) {
    T temp = data_[i];
    data_[i] = data_[j];
    data_[j] = temp;
  }

  // SIFT DOWN -> SIFT DOWN MIN | SIFT DOWN MAX
  void SiftDownMin(int i) {
    int left_child = (2 * i) + 1;
    if (left_child >= (int)data_.size()) {
      return;
    }

    // Находим минимальный среди детей и внуков
    int min_index = left_child;

    // Проверяем правого ребенка
    int right_child = (2 * i) + 2;
    if (right_child < (int)data_.size()) {
      if (data_[right_child] < data_[min_index]) {
        min_index = right_child;
      }
    }

    // Проверяем внуков
    for (int grandchild : {(2 * left_child) + 1, (2 * left_child) + 2,
                           (2 * right_child) + 1, (2 * right_child) + 2}) {
      if (grandchild < (int)data_.size() &&
          data_[grandchild] < data_[min_index]) {
        min_index = grandchild;
      }
    }

    if (min_index != i) {
      if (min_index >= 2 * i + 3) {  // Это внук
        if (data_[min_index] < data_[i]) {
          Swap(min_index, i);
          int parent = (min_index - 1) / 2;
          if (data_[min_index] > data_[parent]) {
            Swap(min_index, parent);
          }
          SiftDownMin(min_index);
        }
      } else {  // Это ребенок
        if (data_[min_index] < data_[i]) {
          Swap(min_index, i);
        }
      }
    }
  }

  void SiftDownMax(int i) {
    int left_child = (2 * i) + 1;
    if (left_child >= (int)data_.size()) {
      return;
    }

    // Находим максимальный среди детей и внуков
    int max_index = left_child;

    // Проверяем правого ребенка
    int right_child = (2 * i) + 2;
    if (right_child < (int)data_.size()) {
      if (data_[right_child] > data_[max_index]) {
        max_index = right_child;
      }
    }

    // Проверяем внуков
    for (int grandchild : {(2 * left_child) + 1, (2 * left_child) + 2,
                           (2 * right_child) + 1, (2 * right_child) + 2}) {
      if (grandchild < (int)data_.size() &&
          data_[grandchild] > data_[max_index]) {
        max_index = grandchild;
      }
    }

    if (max_index != i) {
      if (max_index >= 2 * i + 3) {  // Это внук
        if (data_[max_index] > data_[i]) {
          Swap(max_index, i);
          int parent = (max_index - 1) / 2;
          if (data_[max_index] < data_[parent]) {
            Swap(max_index, parent);
          }
          SiftDownMax(max_index);
        }
      } else {  // Это ребенок
        if (data_[max_index] > data_[i]) {
          Swap(max_index, i);
        }
      }
    }
  }

  void SiftDown(int i) {
    int level = GetLevel(i);
    if (level % 2 == 0)  // Уровень миннимумов
    {
      SiftDownMin(i);
    } else {
      SiftDownMax(i);
    }
  }

  // SIFT UP -> SIFT UP MAX | SIFT UP MIN
  void SiftUpMin(int i) {
    int parent = (i - 1) / 2;
    int grand_parent = (parent - 1) / 2;
    if ((i - 1) / 2 > 0 && data_[i] < data_[grand_parent]) {
      Swap(i, grand_parent);
      SiftUpMin(grand_parent);
    }
  }

  void SiftUpMax(int i) {
    int parent = (i - 1) / 2;
    int grand_parent = (parent - 1) / 2;
    if ((i - 1) / 2 > 0 && data_[i] > data_[grand_parent]) {
      Swap(i, grand_parent);
      SiftUpMax(grand_parent);
    }
  }

  void SiftUp(int i) {
    if (i != 0) {
      int parent = (i - 1) / 2;
      int level = GetLevel(i);
      if (level % 2 == 0) {
        if (data_[i] > data_[parent]) {
          Swap(i, parent);
          SiftUpMax(parent);
        } else {
          SiftUpMin(i);
        }
      } else {
        if (data_[i] < data_[parent]) {
          Swap(i, parent);
          SiftUpMin(parent);
        } else {
          SiftUpMax(i);
        }
      }
    }
  }

 public:
  int GetLevel(int i) {
    int level = 0;
    int x = i + 1;
    while (x > 1) {
      x /= 2;  // делим на 2
      ++level;
    }
    return level;
  }
  void Insert(T i) {
    data_.push_back(i);
    SiftUp(data_.size() - 1);
    std::cout << "ok";
  }

  void ExtractMin() {
    if (data_.empty()) {
      std::cout << "error";
      return;
    }
    std::cout << data_[0];
    if (data_.size() == 1) {
      data_.pop_back();
      return;
    }
    Swap(0, data_.size() - 1);
    data_.pop_back();
    SiftDown(0);
  }

  void GetMin() {
    if (data_.empty()) {
      std::cout << "error";
      return;
    }
    std::cout << data_[0];
  }

  void ExtractMax() {
    if (data_.empty()) {
      std::cout << "error";
      return;
    }

    if (data_.size() == 1) {
      ExtractMin();
      return;
    }

    if (data_.size() == 2) {
      std::cout << data_[1];
      Swap(1, data_.size() - 1);
      data_.pop_back();
      SiftDown(1);
    } else {
      int max_ind = data_[1] >= data_[2] ? 1 : 2;
      std::cout << data_[max_ind];
      Swap(max_ind, data_.size() - 1);
      data_.pop_back();
      SiftDown(max_ind);
    }
  }

  void GetMax() {
    if (data_.empty()) {
      std::cout << "error";
      return;
    }

    if (data_.size() == 1) {
      std::cout << data_[0];
      return;
    }

    if (data_.size() == 2) {
      std::cout << data_[1];
    } else {
      std::cout << (data_[1] >= data_[2] ? data_[1] : data_[2]);
    }
  }

  void Size() { std::cout << data_.size(); }

  void Clear() {
    data_.clear();
    std::cout << "ok";
  }

  void Print() { PrintArray(data_); }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int q{};
  std::cin >> q;
  MaxMinHeap<long long> heap{};

  for (int i{}; i < q; i++) {
    int req{};
    std::cin >> req;
    if (req == 0) {
      long long l{};
      std::cin >> l;
      heap.Insert(l);
    } else if (req == 1) {
      heap.ExtractMin();
    } else if (req == 2) {
      heap.GetMin();
    } else if (req == 3) {
      heap.ExtractMax();
    } else if (req == 4) {
      heap.GetMax();
    } else if (req == 5) {
      heap.Size();
    } else {
      heap.Clear();
    }
    std::cout << "\n";
    // heap.Print();
  }
}