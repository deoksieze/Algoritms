#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

enum Color { White, Gray, Black };

std::vector<std::vector<int>> g;
std::vector<int> color;
std::vector<int> parent;
std::vector<int> tin;
std::vector<int> ret;
std::vector<int> art_points;
int timer = 0;

void Dfs(int v, int parent = -1) {
  color[v] = Black;
  tin[v] = timer;
  ret[v] = timer;
  timer++;

  int children = 0;
  bool is_art = false;

  for (auto to : g[v]) {
    if (to == v || to == parent) {
      continue;
    }

    if (color[to] == White) {
      Dfs(to, v);
      ret[v] = std::min(ret[v], ret[to]);

      if (ret[to] >= tin[v] && parent != -1) {
        is_art = true;
      }

      children++;

    } else {
      ret[v] = std::min(ret[v], tin[to]);
    }
  }

  if (parent == -1 && children > 1) {
    is_art = true;
  }

  if (is_art) {
    art_points.push_back(v);
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
    g[u].push_back(v);
    g[v].push_back(u);
  }

  for (int i = 1; i <= n; i++) {
    if (color[i] == White) {
      Dfs(i);
    }
  }

  std::sort(art_points.begin(), art_points.end());

  std::cout << art_points.size() << "\n";
  for (auto i : art_points) {
    std::cout << i << " ";
  }
  std::cout << "\n";
}