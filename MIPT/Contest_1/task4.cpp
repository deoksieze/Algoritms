#include <cstdint>
#include <iostream>
#include <vector>

int main() {
  constexpr int c256 = 256;
  constexpr int c8 = 8;
  constexpr int cMask = 0xFF;
  int n{0};
  std::cin >> n;

  std::vector<uint64_t> arr(n);
  std::vector<uint64_t> temp(n);

  for (int i{0}; i < n; i++) {
    std::cin >> arr[i];
  }

  std::vector<int> count(c256);

  for (int k{0}; k < c8; k++) {
    std::fill(count.begin(), count.end(), 0);

    for (int i{0}; i < n; i++) {
      size_t byte = (arr[i] >> k * c8) & cMask;
      count[byte]++;
    }

    for (int i{1}; i < c256; i++) {
      count[i] += count[i - 1];
    }

    for (int i{n - 1}; i >= 0; i--) {
      size_t byte = (arr[i] >> k * c8) & cMask;
      count[byte]--;
      temp[count[byte]] = arr[i];
    }

    for (int i{0}; i < n; i++) {
      arr[i] = temp[i];
    }
  }

  for (auto i : arr) {
    std::cout << i << " ";
  }
}
