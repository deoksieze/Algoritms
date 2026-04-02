
#include <algorithm>
#include <ctime>
#include <iostream>
#include <utility>
#include <vector>

enum Color { White, Gray, Black };

std::vector<std::vector<int>> g;
std::vector<int> color;
std::vector<int> parent;
std::vector<int> tin;
std::vector<int> ret;
std::vector<std::pair<int, int>> bridges;
std::vector<int> components;
int timer = 0;

void Dfs(int v, int par = -1) {
  color[v] = Black;
  tin[v] = timer;
  ret[v] = timer;
  timer++;

  for (auto to : g[v]) {
    if (color[to] == White) {
      Dfs(to, v);
      ret[v] = std::min(ret[v], ret[to]);
      if (ret[to] == tin[to]) {
        bridges.push_back({v, to});
      }
    } else if (to != par) {
      ret[v] = std::min(ret[v], tin[to]);
    }
  }
}

void DFSComp(int v, int comp) {
  components[v] = comp;
  color[v] = Black;

  for (auto to : g[v]) {
    if (color[to] == White) {
      DFSComp(to, comp);
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
  components.resize(n + 1, -1);

  int u;
  int v;
  for (int i{1}; i <= m; i++) {
    std::cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  Dfs(1);

  for (auto pair : bridges) {
    int v = pair.first;
    int u = pair.second;
    std::erase(g[u], v);
    std::erase(g[v], u);
  }

  for (int i = 1; i <= n; i++) {
    color[i] = White;
  }

  int counter = 0;
  for (int i = 1; i <= n; i++) {
    if (color[i] == White) {
      DFSComp(i, counter);
      counter++;
    }
  }

  std::vector<int> degree(counter + 1, 0);
  for (auto [u, v] : bridges) {
    degree[components[u]]++;
    degree[components[v]]++;
  }

  int leaves = std::count(degree.begin(), degree.end(), 1);
  std::cout << (leaves + 1) / 2 << "\n";
}