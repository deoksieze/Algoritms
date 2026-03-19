#include <algorithm>
#include <ctime>
#include <iostream>
#include <stack>
#include <vector>

enum Color { White, Gray, Black };

std::vector<std::vector<int>> g;
std::vector<int> color;
std::vector<int> parent;

bool Dfs(int v, std::stack<int>& stack) {
  color[v] = Gray;
  stack.push(v);

  for (auto to : g[v]) {
    if (color[to] == White) {
      if (Dfs(to, stack)) {
        return true;
      }
    } else if (color[to] == Gray) {
      std::cout << "YES\n";
      int i;
      std::vector<int> cycle;
      while (!stack.empty()) {
        i = stack.top();
        cycle.push_back(i);
        stack.pop();
        if (i == to) {
          break;
        }
      }

      std::reverse(cycle.begin(), cycle.end());
      for (auto x : cycle) {
        std::cout << x << " ";
      }
      std::cout << "\n";
      return true;
    }
  }

  color[v] = Black;
  stack.pop();
  return false;
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
  }

  std::stack<int> stack;
  for (int i{1}; i <= n; i++) {
    if (color[i] == White) {
      if (Dfs(i, stack)) {
        return 0;
      }
    }
  }

  std::cout << "NO\n";
}
