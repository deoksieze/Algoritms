#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

struct Triple {
  int i{}, g{}, k{};
  bool operator<(const Triple& other) const {
    return std::tie(i, g, k) < std::tie(other.i, other.g, other.k);
  }
};

int ReadArr(std::vector<std::pair<int, int>>& arr) {
  int n;
  std::cin >> n;
  arr.resize(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i].first;
    arr[i].second = i;
  }
  return n;
}

int main() {
  int search_num;
  std::cin >> search_num;

  std::vector<std::pair<int, int>> a;
  std::vector<std::pair<int, int>> b;
  std::vector<std::pair<int, int>> c;
  int a_n = ReadArr(a);
  int b_n = ReadArr(b);
  int c_n = ReadArr(c);

  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  std::sort(c.begin(), c.end());

  Triple best{a_n, b_n, c_n};
  bool found = false;

  for (int k = 0; k < c_n; ++k) {
    int target = search_num - c[k].first;
    int i = 0;
    int j = b_n - 1;

    while (i < a_n && j >= 0) {
      int sum = a[i].first + b[j].first;
      if (sum == target) {
        Triple cur{a[i].second, b[j].second, c[k].second};
        if (!found || cur < best) {
          best = cur;
        }
        found = true;
        --j;  // чтобы получить минимальные индексы
      } else if (sum < target) {
        ++i;
      } else {
        --j;
      }
    }
  }

  if (!found) {
    std::cout << -1;
  } else {
    std::cout << best.i << " " << best.g << " " << best.k;
  }
}
