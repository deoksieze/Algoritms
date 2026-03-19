
#include <ctime>
#include <iostream>
#include <vector>

enum Color { White, Gray, Black };

std::vector<std::vector<int>> g;
std::vector<int> color;
std::vector<int> parent;

void Dfs(int v, std::vector<int>& vec) {
  color[v] = Black;
  vec.push_back(v);

  for (auto to : g[v]) {
    if (color[to] == White) {
      Dfs(to, vec);
    }
  }
}

int main() {
  int n;
  int m;
  std::cin >> n >> m;

  g.resize(n + 1, std::vector<int>(0));

  color.resize(n + 1);
  parent.resize(n + 1);

  int u;
  int v;
  for (int i{}; i < m; i++) {
    std::cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  std::vector<std::vector<int>> connectivity;  // Все компоненты связности
  for (int i{1}; i <= n; i++) {
    if (color[i] == White) {
      std::vector<int> a;
      connectivity.push_back(a);
      Dfs(i, connectivity[connectivity.size() - 1]);
    }
  }

  std::cout << connectivity.size() << "\n";
  for (auto i : connectivity) {
    std::cout << i.size() << "\n";
    for (auto j : i) {
      std::cout << j << " ";
    }
    std::cout << "\n";
  }
}