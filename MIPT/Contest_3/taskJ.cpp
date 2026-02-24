#include <iostream>
#include <string>
#include <vector>

class BinHeap {
  std::vector<int> data_;
  std::vector<int> request_index_;
  std::vector<int> pos_in_heap_;

  void SwapNodes(int i, int j) {
    std::swap(data_[i], data_[j]);
    std::swap(request_index_[i], request_index_[j]);
    pos_in_heap_[request_index_[i]] = i;
    pos_in_heap_[request_index_[j]] = j;
  }

 public:
  BinHeap(int max_q) { pos_in_heap_.assign(max_q + 1, -1); }

  void SiftUp(int index) {
    while (index > 0) {
      int parent = (index - 1) / 2;
      if (data_[index] < data_[parent]) {
        SwapNodes(index, parent);
        index = parent;
      } else {
        break;
      }
    }
  }

  void SiftDown(int index) {
    int n = data_.size();
    while (true) {
      int l = (2 * index) + 1;
      int r = (2 * index) + 2;
      int smallest = index;
      if (l < n && data_[l] < data_[smallest]) {
        smallest = l;
      }
      if (r < n && data_[r] < data_[smallest]) {
        smallest = r;
      }
      if (smallest == index) {
        break;
      }
      SwapNodes(index, smallest);
      index = smallest;
    }
  }

  void Insert(int x, int query_id) {
    data_.push_back(x);
    request_index_.push_back(query_id);
    pos_in_heap_[query_id] = data_.size() - 1;
    SiftUp(data_.size() - 1);
  }

  int GetMin() const { return data_.empty() ? -1 : data_[0]; }

  void ExtractMin() {
    if (data_.empty()) {
      return;
    }
    int last = data_.size() - 1;
    pos_in_heap_[request_index_[0]] = -1;
    if (last > 0) {
      data_[0] = data_[last];
      request_index_[0] = request_index_[last];
      pos_in_heap_[request_index_[0]] = 0;
    }
    data_.pop_back();
    request_index_.pop_back();
    if (!data_.empty()) {
      SiftDown(0);
    }
  }

  void DecreaseKey(int query_id, int delta) {
    int idx = pos_in_heap_[query_id];
    if (idx == -1) {
      return;
    }  // этот элемент уже извлечён
    data_[idx] -= delta;
    SiftUp(idx);
  }
};

std::vector<std::string> Split(const std::string& s) {
  std::vector<std::string> result;
  std::string token;
  for (char c : s) {
    if (c == ' ' || c == '\t') {
      if (!token.empty()) {
        result.push_back(token);
        token.clear();
      }
    } else {
      token += c;
    }
  }
  if (!token.empty()) {
    result.push_back(token);
  }
  return result;
}

int main() {
  int q{};
  std::cin >> q;
  std::string line;
  std::getline(std::cin, line);

  BinHeap heap(q);
  std::string answer;

  for (int query_id = 1; query_id <= q; ++query_id) {
    std::getline(std::cin, line);
    if (line.empty()) {
      continue;
    }

    auto parts = Split(line);
    const std::string& cmd = parts[0];

    if (cmd == "insert") {
      int x = std::stoi(parts[1]);
      heap.Insert(x, query_id);
    } else if (cmd == "decreaseKey") {
      int i = std::stoi(parts[1]);
      int delta = std::stoi(parts[2]);
      heap.DecreaseKey(i, delta);
    } else if (cmd == "getMin") {
      answer += std::to_string(heap.GetMin()) + "\n";
    } else if (cmd == "extractMin") {
      heap.ExtractMin();
    }
  }

  std::cout << answer;
}
