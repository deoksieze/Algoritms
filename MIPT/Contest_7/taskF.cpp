
#include <cstddef>
#include <iostream>
#include <vector>

struct Obj {
  int color;
  int cost;
  int weight;
  ~Obj() = default;
};

int main() {
  int n;
  int g;
  int m;
  std::cin >> n >> g >> m;

  std::vector<std::vector<Obj>> color_sets(g + 1);
  for (int i{}; i < n; i++) {
    Obj obj;
    std::cin >> obj.weight >> obj.cost >> obj.color;
    color_sets[obj.color].push_back(obj);
  }

  std::vector<std::vector<int>> dp(g + 1, std::vector<int>(m + 1, 0));
  for (int i{}; i <= g; i++) {
    for (int a = m; a >= 0; a--) {
      if (a == 0 || i == 0) {
        dp[i][a] = 0;
        continue;
      }

      dp[i][a] = dp[i - 1][a];
      for (size_t j{}; j < color_sets[i].size(); j++) {
        int w = color_sets[i][j].weight;
        int c = color_sets[i][j].cost;
        if (a >= w) {
          dp[i][a] = std::max(dp[i][a], dp[i - 1][a - w] + c);
        }
      }
    }
  }

  std::cout << dp[g][m] << "\n";
}