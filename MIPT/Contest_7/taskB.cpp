#include <algorithm>
#include <climits>
#include <cstddef>
#include <iostream>
#include <vector>

long long Cost(std::vector<long long>& pref, std::vector<long long>& vec,
               size_t l, size_t r) {
  if (l > r) {
    return 0;
  }
  size_t m = (l + r) / 2;
  return (pref[r + 1] - 2 * pref[m + 1] + pref[l]) +
         (vec[m] * ((2 * m) - l - r + 1));
}

int main() {
  int n;
  int m;
  std::cin >> n >> m;

  std::vector<long long> vec(n);
  std::vector<long long> pref(n + 1, 0);

  for (int i = 0; i < n; i++) {
    std::cin >> vec[i];
    pref[i + 1] = pref[i] + vec[i];
  }

  std::vector<std::vector<long long>> dp(
      n + 1, std::vector<long long>(m + 1, LLONG_MAX / 2));

  std::vector<std::vector<int>> parent(n + 1, std::vector<int>(m + 1, -1));

  for (int i = 1; i <= n; i++) {
    dp[i][1] = Cost(pref, vec, 0, i - 1);
    parent[i][1] = 0;
  }

  for (int k = 2; k <= m; k++) {
    for (int i = k; i <= n; i++) {
      for (int j = k - 1; j < i; j++) {
        long long cost = Cost(pref, vec, j, i - 1);
        if (dp[j][k - 1] + cost < dp[i][k]) {
          dp[i][k] = dp[j][k - 1] + cost;
          parent[i][k] = j;
        }
      }
    }
  }

  std::vector<long long> wells;
  int cur = n;
  int k_left = m;

  while (k_left > 0) {
    int prev = parent[cur][k_left];
    int median_idx = (prev + cur - 1) / 2;
    wells.push_back(vec[median_idx]);
    cur = prev;
    k_left--;
  }

  std::reverse(wells.begin(), wells.end());

  std::cout << dp[n][m] << "\n";
  for (auto w : wells) {
    std::cout << w << " ";
  }
  std::cout << "\n";

  return 0;
}