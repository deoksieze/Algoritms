#include <cstdint>
#include <iostream>
#include <vector>

struct Segment {
  int64_t start;
  int64_t end;

  int64_t Length() const { return end - start + 1; }

  bool operator>(const Segment& other) const {
    if (Length() != other.Length()) {
      return Length() > other.Length();
    }
    return start < other.start;
  }
};

template <typename T>
class MaxHeap {
 public:
  std::vector<T> data;

  void Swap(int i, int j) { std::swap(data[i], data[j]); }

  void SiftUp(int i) {
    while (i > 0) {
      int p = (i - 1) / 2;
      if (data[i] > data[p]) {
        Swap(i, p);
        i = p;
      } else {
        break;
      }
    }
  }

  void SiftDown(int i) {
    int n = static_cast<int>(data.size());
    while (true) {
      int l = (2 * i) + 1;
      int r = (2 * i) + 2;
      int largest = i;
      if (l < n && data[l] > data[largest]) {
        largest = l;
      }
      if (r < n && data[r] > data[largest]) {
        largest = r;
      }
      if (largest == i) {
        break;
      }
      Swap(i, largest);
      i = largest;
    }
  }

  void Insert(T val) {
    data.push_back(val);
    SiftUp(static_cast<int>(data.size()) - 1);
  }

  void RemoveMax() {
    if (data.empty()) {
      return;
    }
    data[0] = data.back();
    data.pop_back();
    if (!data.empty()) {
      SiftDown(0);
    }
  }

  T GetMax() const { return data[0]; }

  bool IsEmpty() const { return data.empty(); }
};

void PrintArray(std::vector<Segment>& i) {
  for (auto j : i) {
    std::cout << "[" << j.start << ";" << j.end << "]" << " ";
  }
  std::cout << "\n";
}

int main() {
  //   std::ios_base::sync_with_stdio(false);
  //   std::cin.tie(nullptr);

  int64_t q{};
  int64_t n{};
  std::cin >> n >> q;

  MaxHeap<Segment> heap{};
  heap.Insert({1, n});
  std::vector<Segment> requests(q + 1);
  PrintArray(heap.data);

  for (int64_t i{1}; i <= q; i++) {
    int64_t k{};
    std::cin >> k;
    if (k >= 1) {
      if (heap.GetMax().Length() < k) {
        std::cout << -1;
        requests[k] = {-1, -1};
      } else {
        Segment seg = heap.GetMax();
        heap.RemoveMax();
        seg.start = seg.start + k;
        heap.Insert(seg);
        requests[k] = seg;
      }
    }

    PrintArray(heap.data);
  }
}