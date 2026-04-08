
#include <iostream>
#include <vector>
int main() {
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> g(n + 1, std::vector<int>(n + 1, 0));

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int x;
      std::cin >> x;
      g[i][j] = x;
    }
  }

  for (int i{1}; i <= n; i++) {
    g[i][i] = 1;
  }

  for (int i = 1; i <= n; i++) {
    for (int u = 1; u <= n; u++) {
      for (int v = 1; v <= n; v++) {
        if (g[u][i] == 0 || g[i][v] == 0) {
          continue;
        }

        g[u][v] = 1;
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      std::cout << g[i][j] << " ";
    }
    std::cout << "\n";
  }
}