#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

const int cBigNumber = 1e9;

int main() {
  std::string u;
  std::string v;
  int k;

  std::cin >> u >> v >> k;

  int n = u.size();
  int m = v.size();

  std::vector dp(n + 1,
                 std::vector(m + 1, std::vector<int>(k + 1, cBigNumber)));

  dp[0][0][0] = 0;

  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      for (int t = 0; t <= k; ++t) {
        if (dp[i][j][t] == cBigNumber) {
          continue;
        }
        int cur = dp[i][j][t];

        if (i < n && t + 1 <= k) {
          dp[i + 1][j][t + 1] = std::min(dp[i + 1][j][t + 1], cur);
        }

        if (j < m && t + 1 <= k) {
          dp[i][j + 1][t + 1] = std::min(dp[i][j + 1][t + 1], cur);
        }

        if (i < n && j < m) {
          int edit_cost;
          edit_cost = (u[i] != v[j]) ? 1 : 0;
          if (t + edit_cost <= k) {
            dp[i + 1][j + 1][t + edit_cost] =
                std::min(dp[i + 1][j + 1][t + edit_cost], cur);
          }

          edit_cost = (u[i] == v[j]) ? 1 : 0;

          if (t + edit_cost <= k) {
            dp[i + 1][j + 1][t + edit_cost] =
                std::min(dp[i + 1][j + 1][t + edit_cost], cur + 1);
          }
        }
      }
    }
  }

  int ans = cBigNumber;
  for (int t = 0; t <= k; ++t) {
    ans = std::min(ans, dp[n][m][t]);
  }
  if (ans == cBigNumber) {
    std::cout << -1 << "\n";
  } else {
    std::cout << ans << "\n";
  }
  return 0;
}