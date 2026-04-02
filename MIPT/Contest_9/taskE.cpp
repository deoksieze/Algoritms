#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int from;
  int to;
  int w;
};

int main() {
  const int cInf = 100000;
  int n;
  std::cin >> n;

  std::vector<Edge> edges;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      int w;
      std::cin >> w;
      if (w != cInf) {
        edges.push_back({i, j, w});
      }
    }
  }

  std::vector<long long> dist(n + 1, 0);
  std::vector<int> parent(n + 1, -1);

  int last = -1;

  for (int i = 1; i <= n; ++i) {
    last = -1;
    for (const auto& e : edges) {
      if (dist[e.to] > dist[e.from] + e.w) {
        dist[e.to] = dist[e.from] + e.w;
        parent[e.to] = e.from;
        last = e.to;
      }
    }
  }

  if (last == -1) {
    std::cout << "NO\n";
    return 0;
  }

  int v = last;
  for (int i = 0; i < n; ++i) {
    v = parent[v];
  }

  std::vector<int> cycle;
  int cur = v;
  do {
    cycle.push_back(cur);
    cur = parent[cur];
  } while (cur != v);
  cycle.push_back(v);

  std::reverse(cycle.begin(), cycle.end());

  std::cout << "YES\n";
  std::cout << cycle.size() << "\n";
  for (int x : cycle) {
    std::cout << x << " ";
  }
  std::cout << "\n";

  return 0;
}