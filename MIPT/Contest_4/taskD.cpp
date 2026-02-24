#include <cmath>
#include <iostream>
#include <vector>

std::pair<int, int> GetSegmentRange(int i, int n) {
  const int c31 = 31;
  int node_level = c31 - __builtin_clz(i);

  int nodes_on_level = 1 << node_level;
  int offset = i - nodes_on_level;
  int segment_size = n / nodes_on_level;
  int l = offset * segment_size;
  int r = l + segment_size - 1;

  if (r >= n) {
    r = n - 1;
  }
  return {l + 1, r + 1};
}

int Max(int x, int y) { return x > y ? x : y; }

void TreeBuild(std::vector<int>& t, std::vector<int>& a) {
  size_t n{a.size()};
  for (size_t i{}; i < n; i++) {
    t[n + i] = a[i];
  }

  for (int i{static_cast<int>(n - 1)}; i > 0; i--) {
    t[i] = Max(t[2 * i], t[(2 * i) + 1]);
  }
}

void Update(std::vector<int>& t, int n, int pos, int val) {
  pos += n;
  t[pos] = val;
  for (pos /= 2; pos >= 1; pos /= 2) {
    t[pos] = Max(t[2 * pos], t[(2 * pos) + 1]);
  }
}

int Get(std::vector<int>& t, int n, int pos, int x) {
  int start_pos = pos;
  pos += n;
  // Поднимаемся наверх
  while (t[pos] < x) {
    if (pos % 2 == 1) {
      pos--;
    }
    pos /= 2;

    if (GetSegmentRange(pos, n).first < start_pos) {
      return -1;
    }
  }

  // Идем вниз
  //   std::cout << pos << " ";
  while (2 * pos + 1 < (int)t.size()) {
    if (t[2 * pos] >= x) {
      pos = 2 * pos;
    } else {
      pos = (2 * pos) + 1;
    }
    // std::cout << pos << " ";
  }

  //   std::cout << pos << " " << t[pos];
  return pos - n;
}

int main() {
  int n{};
  int q{};
  std::cin >> n >> q;
  int len{2};
  while (len < n) {
    len *= 2;
  }

  std::vector<int> a(len);
  for (int i{}; i < n; i++) {
    std::cin >> a[i];
  }

  std::vector<int> t(2 * len);
  TreeBuild(t, a);

  for (int i{}; i < q; i++) {
    int operation{};
    int ind;
    int val;
    std::cin >> operation >> ind >> val;
    if (operation == 0) {
      Update(t, len - 1, ind, val);
    } else {
      std::cout << Get(t, len - 1, ind, val) << "\n";
    }
  }
}