#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  long long n;
  std::cin >> n;

  std::vector<long long> arr(n);
  for (long long i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }

  if (n == 0) {
    std::cout << 0 << std::endl;
    return 0;
  }

  std::vector<std::pair<long long, long long>> tailes;
  std::vector<long long> prev(n, -1);
  std::vector<long long> pos_in_tails(n);

  for (long long i = 0; i < n; ++i) {
    long long left = 0;
    long long right = tailes.size();
    while (left < right) {
      long long mid = left + ((right - left) / 2);
      if (tailes[mid].first < arr[i]) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }

    long long pos = left;

    if (pos < static_cast<long long>(tailes.size())) {
      tailes[pos] = {arr[i], i};
    } else {
      tailes.push_back({arr[i], i});
    }

    pos_in_tails[i] = pos;

    if (pos > 0) {
      prev[i] = tailes[pos - 1].second;
    }
  }

  std::vector<long long> result;
  if (tailes.empty()) {
    std::cout << 0 << std::endl;
    return 0;
  }

  long long current = tailes.back().second;
  while (current != -1) {
    result.push_back(current + 1);
    current = prev[current];
  }

  std::reverse(result.begin(), result.end());

  std::cout << result.size() << std::endl;
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << result[i] << " ";
  }
  std::cout << std::endl;

  return 0;
}