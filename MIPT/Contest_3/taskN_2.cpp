#include <algorithm>
#include <cstdint>
#include <iostream>
#include <set>
#include <vector>

struct Segment {
  int64_t start;
  int64_t end;

  int64_t Lenght() const { return end - start + 1; }

  bool operator>(const Segment& other) const {
    if (Lenght() != other.Lenght()) {
      return Lenght() > other.Lenght();
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

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int64_t n;
  int64_t q;
  std::cin >> n >> q;

  MaxHeap<Segment> free_heap;
  std::set<std::pair<int64_t, int64_t>> free_set;
  std::vector<std::pair<int64_t, int64_t>> allocated(q + 1, {-1, -1});

  free_set.insert({1, n});
  free_heap.Insert({1, n});

  for (int64_t i = 1; i <= q; ++i) {
    int64_t k;
    std::cin >> k;

    if (k > 0) {
      bool allocated_success = false;

      while (!free_heap.IsEmpty()) {
        Segment seg = free_heap.GetMax();

        auto it = free_set.find({seg.start, seg.end});
        if (it == free_set.end()) {
          free_heap.RemoveMax();
          continue;
        }

        if (seg.Lenght() < k) {
          break;
        }

        free_set.erase(it);
        free_heap.RemoveMax();

        std::cout << seg.start << '\n';
        allocated[i] = {seg.start, k};

        if (seg.Lenght() > k) {
          Segment new_seg = {seg.start + k, seg.end};
          free_set.insert({new_seg.start, new_seg.end});
          free_heap.Insert(new_seg);
        }

        allocated_success = true;
        break;
      }

      if (!allocated_success) {
        std::cout << -1 << '\n';
      }
    } else {
      int64_t idx = -k;
      if (idx < 1 || idx >= i || allocated[idx].first == -1) {
        continue;
      }

      int64_t start = allocated[idx].first;
      int64_t size = allocated[idx].second;
      int64_t end = start + size - 1;

      Segment new_seg = {start, end};

      auto it = free_set.lower_bound({start, 0});
      if (it != free_set.begin()) {
        auto prev_it = std::prev(it);
        if (prev_it->second == start - 1) {
          new_seg.start = prev_it->first;
          free_set.erase(prev_it);
        }
      }

      it = free_set.lower_bound({end + 1, 0});
      if (it != free_set.end() && it->first == end + 1) {
        new_seg.end = it->second;
        free_set.erase(it);
      }

      free_set.insert({new_seg.start, new_seg.end});
      free_heap.Insert(new_seg);

      allocated[idx] = {-1, -1};
    }
  }

  return 0;
}