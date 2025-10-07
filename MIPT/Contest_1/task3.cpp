#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

int const cMaxPoint = 1000000000;

template <typename T>
bool IsEnough(T first, T last, long long length, int sections_threshold) {
  if (first == last) {
    return true;
  }

  int sections_spent = 1;
  auto begin_point = *first;

  for (auto it = first; it != last; ++it) {
    if (*it > begin_point + length) {
      sections_spent++;
      // std::cout << *it << " " << begin_point << " " << length << " " <<
      // sections_spent <<  "\n";
      begin_point = *it;
      if (sections_spent > sections_threshold) {
        return false;
      }
    }
  }

  return true;
}

int main() {
  size_t n{};
  int k{};
  std::cin >> n >> k;
  std::vector<int> arr(n);

  for (size_t i = 0; i < n; i++) {
    std::cin >> arr[i];
  }

  std::sort(arr.begin(), arr.end());

  int left{-1};
  int right{cMaxPoint};

  while (right - left > 1) {
    int mid = (right + left) / 2;

    if (IsEnough(arr.begin(), arr.end(), mid, k)) {
      right = mid;
    } else {
      left = mid;
    }
  }

  std::cout << right << '\n';
}