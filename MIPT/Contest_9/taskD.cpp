
#include <climits>
#include <iostream>
#include <utility>
#include <vector>

int main() {
  const int cInf = 30000;
  int n;
  int m;
  std::cin >> n >> m;

  std::vector<std::vector<std::pair<int, int>>> g(n + 1);
  for (int i = 0; i < m; i++) {
    int v;
    int u;
    int w;
    std::cin >> v >> u >> w;

    g[u].push_back({v, w});
  }

  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, cInf));

  dp[0][1] = 0;

  for (int k = 1; k < n; k++) {
    for (int v = 1; v <= n; v++) {
      dp[k][v] = dp[k - 1][v];
      for (auto e : g[v]) {
        int u = e.first;
        int w = e.second;
        if (dp[k - 1][u] != cInf) {
          dp[k][v] = std::min(dp[k - 1][u] + w, dp[k][v]);
        }
      }
    }
  }

  //   for (int k = 0; k < n; k++) {
  //     for (int v = 1; v <= n; v++) {
  //       std::cout << dp[k][v] << " ";
  //     }
  //     std::cout << "\n";
  //   }

  for (int v = 1; v <= n; v++) {
    std::cout << dp[n - 1][v] << " ";
  }

  std::cout << "\n";
}