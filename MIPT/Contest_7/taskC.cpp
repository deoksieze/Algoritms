#include <algorithm>
#include <iostream>

bool Can(int t, int k, int n) {
  long long sum = 0;
  long long comb = 1;
  int limit = std::min(k, t);
  for (int i = 0; i <= limit; ++i) {
    sum += comb;
    if (sum >= n) {
      return true;
    }
    if (i == limit) {
      break;
    }

    comb = comb * (t - i) / (i + 1);
  }
  return false;
}

int main() {
  int n;
  int k;
  std::cin >> n >> k;

  if (n == 1) {
    std::cout << 0 << std::endl;
    return 0;
  }

  if (k == 0) {
    std::cout << -1 << std::endl;
    return 0;
  }

  int lo = 0;
  int hi = n;
  int ans = -1;
  while (lo <= hi) {
    int mid = (lo + hi) / 2;
    if (Can(mid, k, n)) {
      ans = mid;
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }

  std::cout << ans << std::endl;
  return 0;
}