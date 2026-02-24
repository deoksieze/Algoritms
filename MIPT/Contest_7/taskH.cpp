#include <iostream>
#include <vector>
int main() {
  long long n{};
  std::cin >> n;

  long long ans{};

  for (long long d = 1; d <= n; d++) {
    long long target = n - d;
    if (target < 0) {
      continue;
    }

    std::vector<long long> dp(target + 1);
    dp[0] = 1;

    for (long long x{d + 1}; x <= 2 * d - 1; x++) {
      for (long long s{target}; s >= x; s--) {
        dp[s] += dp[s - x];
      }
    }

    ans += dp[target];
  }

  std::cout << ans << "\n";
}
