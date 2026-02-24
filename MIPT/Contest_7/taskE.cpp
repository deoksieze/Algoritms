
#include <iostream>
#include <vector>

struct Ans {
  int cost = 0;
  std::vector<int> ind;

  Ans() = default;
  Ans(const Ans&) = default;
  Ans& operator=(const Ans&) = default;
  ~Ans() = default;
};

int main() {
  int n;
  int m;
  std::cin >> n >> m;

  std::vector<int> w(n);
  std::vector<int> c(n);
  for (int i{}; i < n; i++) {
    std::cin >> w[i];
  }
  for (int i{}; i < n; i++) {
    std::cin >> c[i];
  }

  std::vector<std::vector<Ans>> dp(n + 1, std::vector<Ans>(m + 1));

  for (int i{}; i <= n; i++) {
    for (int a{}; a <= m; a++) {
      if (i == 0 || a == 0) {
        dp[i][a].cost = 0;
        continue;
      }
      dp[i][a] = dp[i - 1][a];

      if (a >= w[i - 1] &&
          dp[i][a].cost < (dp[i - 1][a - w[i - 1]].cost + c[i - 1])) {
        dp[i][a] = dp[i - 1][a - w[i - 1]];
        dp[i][a].cost += c[i - 1];
        dp[i][a].ind.push_back(i);
      }
    }
  }

  //   for (auto i : dp) {
  //     for (auto j : i) {
  //       std::cout << j << " ";
  //     }
  //     std::cout << "\n";
  //   }

  for (auto i : dp[n][m].ind) {
    std::cout << i << "\n";
  }
}