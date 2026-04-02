
#include <cstdint>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

std::vector<std::vector<std::pair<int, int>>> g;
std::vector<long long> coef;
std::vector<long long> free_part;
std::vector<int> d;
int t;
long long sum_coef{};
long long sum_free{};

void BFS(int u) {
  coef[u] = 1;
  d[u] = 0;
  std::queue<int> q;
  q.push(u);
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (auto x : g[v]) {
      int to = x.first;
      int s = x.second;
      if (d[to] == INT32_MAX) {
        coef[to] = -coef[v];
        free_part[to] = s - free_part[v];

        d[to] = d[v] + 1;
        q.push(to);
      }
    }
  }
}

int main() {
  int n;
  int m;
  std::cin >> n >> m;

  g.resize(n + 1);
  d.resize(n + 1, INT32_MAX);
  free_part.resize(n + 1);
  coef.resize(n + 1);

  int u;
  int v;
  int w;
  for (int i{1}; i <= m; i++) {
    std::cin >> u >> v >> w;
    g[u].push_back({v, w});
    g[v].push_back({u, w});
  }

  BFS(1);

  for (int i = 1; i <= n; i++) {
    sum_coef += coef[i];
    sum_free += free_part[i];
  }

  if (sum_coef != 0) {
    t = ((long long)n * (n + 1) / 2 - sum_free) / sum_coef;
    for (int i = 1; i <= n; i++) {
      std::cout << coef[i] * t + free_part[i] << "\n";
    }
  } else {
    long long t_min = 1;
    long long t_max = n;

    for (int i = 1; i <= n; i++) {
      if (coef[i] == 1) {
        t_min = std::max(t_min, 1LL - free_part[i]);
        t_max = std::min(t_max, (long long)n - free_part[i]);
      } else {
        t_min = std::max(t_min, free_part[i] - (long long)n);
        t_max = std::min(t_max, free_part[i] - 1LL);
      }
    }

    for (long long candidate = t_min; candidate <= t_max; candidate++) {
      std::vector<bool> seen(n + 1, false);
      bool ok = true;
      for (int i = 1; i <= n; i++) {
        long long val = coef[i] * candidate + free_part[i];
        if (val < 1 || val > n || seen[val]) {
          ok = false;
          break;
        }
        seen[val] = true;
      }
      if (ok) {
        for (int i = 1; i <= n; i++) {
          std::cout << coef[i] * candidate + free_part[i] << "\n";
        }
        return 0;
      }
    }
  }
}