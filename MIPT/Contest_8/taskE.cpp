#include <algorithm>
#include <ctime>
#include <iostream>
#include <utility>
#include <vector>

enum Color { White, Gray, Black };

std::vector<std::vector<std::pair<int, int>>> g;
std::vector<int> color;
std::vector<int> parent;
std::vector<int> tin;
std::vector<int> ret;
std::vector<int> bridges;
int timer = 0;

void Dfs(int v, int p = -1) {
  color[v] = Black;
  tin[v] = timer;
  ret[v] = timer;
  timer++;

  for (auto x : g[v]) {
    int to = x.first;
    int id = x.second;

    if (p == id) {
      continue;
    }

    if (color[to] == White) {
      Dfs(to, id);
      ret[v] = std::min(ret[v], ret[to]);
      if (ret[to] == tin[to]) {
        bridges.push_back(id);
      }
    } else {
      ret[v] = std::min(ret[v], tin[to]);
    }
  }
}

int main() {
  int n;
  int m;
  std::cin >> n >> m;

  g.resize(n + 1);
  color.resize(n + 1);
  parent.resize(n + 1);
  tin.resize(n + 1);
  ret.resize(n + 1);

  int u;
  int v;
  for (int i{1}; i <= m; i++) {
    std::cin >> u >> v;
    g[u].push_back({v, i});
    g[v].push_back({u, i});
  }

  for (int i = 1; i <= n; i++) {
    if (color[i] == White) {
      Dfs(i);
    }
  }

  std::cout << bridges.size() << "\n";
  std::sort(bridges.begin(), bridges.end());
  for (auto i : bridges) {
    std::cout << i << " ";
  }
  std::cout << "\n";
}