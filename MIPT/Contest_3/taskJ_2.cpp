#include <iostream>
#include <string>
#include <vector>

template <typename T>
void PrintArray(std::vector<T>& i) {
  for (auto j : i) {
    std::cout << j << " ";
  }
  std::cout << "\n";
}

template <typename T>
class Binheap {
 private:
  std::vector<int>
      ind_of_req_;  // Тут для каждого запроса лежит его позиция в data;
  std::vector<int> req_of_ind_;  // Тут для каждого элемента data лежит на каким
                                 // запросом он был положен изначально в data

  void Swap(int ind1, int ind2) {
    std::swap(ind_of_req_[req_of_ind_[ind1]], ind_of_req_[req_of_ind_[ind2]]);
    std::swap(req_of_ind_[ind1], req_of_ind_[ind2]);
    std::swap(data[ind1], data[ind2]);
  }

  void SiftUp(int i) {
    while (i > 0) {
      int p = (i - 1) / 2;
      if (data[i] < data[p]) {
        Swap(i, p);
        i = p;
      } else {
        break;
      }
    }
  }

  void SiftDown(int i) {
    int n = (int)data.size();
    while (true) {
      int l = (2 * i) + 1;
      int r = (2 * i) + 2;
      int smallest = i;
      if (l < n && data[l] < data[smallest]) {
        smallest = l;
      }
      if (r < n && data[r] < data[smallest]) {
        smallest = r;
      }
      if (smallest == i) {
        break;
      }
      Swap(i, smallest);
      i = smallest;
    }
  }

 public:
  std::vector<T> data;

  Binheap(int q) {
    ind_of_req_.resize(q);
    data.reserve(q);
    req_of_ind_.reserve(q);
  }

  long long GetMin() { return data[0]; }

  void Insert(T elem, int req_num) {
    data.push_back(elem);
    ind_of_req_[req_num] = data.size() - 1;
    req_of_ind_.push_back(req_num);

    SiftUp(data.size() - 1);
  }

  void ExtractMin() {
    Swap(0, data.size() - 1);
    int req = req_of_ind_[data.size() - 1];
    ind_of_req_[req] = 0;
    req_of_ind_.pop_back();
    data.pop_back();
    SiftDown(0);
  }

  void DecreaseKey(int req, T delta) {
    int ind = ind_of_req_[req];
    data[ind] -= delta;
    SiftUp(ind);
  }

  void PrintArr(int choice) {
    switch (choice) {
      case (1):
        PrintArray(data);
        return;
      case (2):
        PrintArray(ind_of_req_);
        return;
      case (3):
        PrintArray(req_of_ind_);
        return;
      default:
        return;
    }
  }
};

int main() {
  int const c12 = 12;
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int q;
  std::cin >> q;
  Binheap<long long> heap(q + 1);

  std::string answer;
  answer.reserve(q * c12);

  std::string cmd;
  for (int i = 1; i <= q; ++i) {
    std::cin >> cmd;
    if (cmd == "insert") {
      long long x;
      std::cin >> x;
      heap.Insert(x, i);
    } else if (cmd == "getMin") {
      answer += std::to_string(heap.GetMin()) + '\n';
    } else if (cmd == "extractMin") {
      heap.ExtractMin();
    } else if (cmd == "decreaseKey") {
      int req;
      long long delta;
      std::cin >> req >> delta;
      heap.DecreaseKey(req, delta);
    }
  }

  std::cout << answer;
}
