#include <iostream>
#include <vector>

using VecInt = std::vector<int>;
using It = std::vector<int>::iterator;
const int c1 = 123;
const int c2 = 45;
const int c3 = 10000000 + 4321;
int QuickSelect(It first, It last, size_t k);

template <typename It>
void InsertionSort(It first, It last) {
  for (auto i = first + 1; i < last; ++i) {
    auto key = *i;
    auto j = i;
    while (j > first && *(j - 1) > key) {
      *j = *(j - 1);
      --j;
    }
    *j = key;
  }
}

int PickPivot(It first, It last) {
  size_t size = last - first;
  if (size <= 5) {
    InsertionSort(first, last);
    return *(first + size / 2);
  }

  VecInt medians{};
  medians.reserve((size + 4) / 5);
  for (size_t i = 0; i < size; i += 5) {
    size_t chunk_end = i + 5 < size ? i + 5 : size;
    InsertionSort(first + i, first + chunk_end);
    size_t chunk_len = chunk_end - i;
    *(first + i);
    medians.push_back(*(first + i + (chunk_len / 2)));
  }

  return QuickSelect(medians.begin(), medians.end(), medians.size() / 2);
}

int QuickSelect(It first, It last, size_t k) {
  size_t len = static_cast<size_t>(last - first);
  if (len == 0) {
    return 0;
  }
  if (len == 1) {
    return *first;
  }

  int pivot = PickPivot(first, last);

  auto left = first;
  auto right = last - 1;
  while (left < right) {
    while (*left < pivot) {
      left++;
    }
    while (*right > pivot) {
      right--;
    }

    if (left <= right) {
      std::swap(*left, *right);
      left++;
      right--;
    }
  }

  size_t left_size =
      (right >= first) ? static_cast<size_t>(right - first + 1) : 0;
  size_t middle_size = static_cast<size_t>(left - first) - left_size;
  if (k < left_size) {
    return QuickSelect(first, right + 1, k);
  }
  if (k < left_size + middle_size) {
    return pivot;
  }
  return QuickSelect(left, last, k - left_size - middle_size);
}

int DoRecur(int x, int y) { return (c1 * x + c2 * y) % c3; }

int main() {
  int n{};
  int k{};
  int a0{};
  int a1{};
  std::cin >> n >> k >> a0 >> a1;

  VecInt arr;
  arr.reserve(n);
  arr.push_back(a0);
  arr.push_back(a1);
  for (int i = 2; i < n; i++) {
    int ai = DoRecur(arr[i - 1], arr[i - 2]);
    arr.push_back(ai);
  }
  std::cout << QuickSelect(arr.begin(), arr.end(), k - 1);
}