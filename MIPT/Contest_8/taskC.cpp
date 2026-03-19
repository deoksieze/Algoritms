
#include <algorithm>
#include <iostream>
#include <vector>

enum Color { White, Gray, Black };

std::vector<std::vector<int>> g;
std::vector<int> color;
std::vector<int> order;
bool has_cycle = false;

void Dfs(int v) {
  color[v] = Gray;

  for (auto to : g[v]) {
    if (color[to] == White) {
      Dfs(to);
    } else if (color[to] == Gray) {
      has_cycle = true;
    }
  }

  order.push_back(v);
  color[v] = Black;
}

int main() {
  int n;
  int m;
  std::cin >> n >> m;

  g.resize(n + 1, std::vector<int>(0));

  color.resize(n + 1);

  int u;
  int v;
  for (int i{}; i < m; i++) {
    std::cin >> u >> v;
    g[u].push_back(v);
  }

  for (int i = 1; i <= n; i++) {
    if (color[i] == White) {
      Dfs(i);
    }
  }

  if (has_cycle) {
    std::cout << -1 << "\n";
    return 0;
  }

  std::reverse(order.begin(), order.end());
  for (int i = 0; (size_t)i < order.size(); i++) {
    std::cout << order[i] << " ";
  }
  std::cout << "\n";
}