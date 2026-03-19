
#include <algorithm>
#include <iostream>
#include <vector>

enum Color { White, Gray, Black };

std::vector<std::vector<int>> g;
std::vector<int> color;
std::vector<int> order;

std::vector<std::vector<int>> c;
int kss_counter = 1;
std::vector<int> kss_num;

void Dfs(int v) {
  color[v] = Gray;

  for (auto to : g[v]) {
    if (color[to] == White) {
      Dfs(to);
    }
  }

  order.push_back(v);
  color[v] = Black;
}

void Dfs2(int v) {
  color[v] = Gray;
  kss_num[v] = kss_counter;

  for (auto to : c[v]) {
    if (color[to] == White) {
      Dfs2(to);
    }
  }

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

  std::reverse(order.begin(), order.end());

  // Начинаем решать задачу Косарайю

  c.resize(n + 1, std::vector<int>(0));  // массив обратный ребер
  kss_num.resize(n + 1);

  for (int i{1}; i <= n; i++) {
    color[i] = White;

    for (auto v : g[i]) {
      c[v].push_back(i);
    }
  }

  for (auto v : order) {
    if (color[v] == White) {
      Dfs2(v);
      kss_counter++;
    }
  }

  std::cout << kss_counter - 1 << "\n";
  for (int i = 1; i <= n; i++) {
    std::cout << kss_num[i] << " ";
  }
  std::cout << "\n";
}