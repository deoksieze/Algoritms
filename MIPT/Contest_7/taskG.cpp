
#include <iostream>
#include <vector>
int main() {
  long long n;
  std::cin >> n;

  std::vector<std::vector<long long>> dp(n + 1, std::vector<long long>(n + 1));

  for (long long i{1}; i <= n; i++) {
    for (long long k{}; k <= n; k++) {
      if (k == i) {
        dp[i][k] = 1;
        continue;
      }
      if (k > i) {
        dp[i][k] = 0;
        continue;
      }

      for (long long j{1}; j <= k / 2; j++) {
        dp[i][k] += dp[i - k][j];
      }
    }
  }

  long long ans{};
  for (long long i{}; i <= n; i++) {
    ans += dp[n][i];
  }
  std::cout << ans << "\n";

  //   for (auto i : dp) {
  //     for (auto j : i) {
  //       std::cout << j << " ";
  //     }

  //     std::cout << "\n";
  //   }
}
