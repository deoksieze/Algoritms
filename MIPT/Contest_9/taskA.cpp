
#include <ios>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

struct Edge {
  int to;
  int len;
};

std::vector<int> d;
std::vector<bool> used;
std::vector<std::vector<Edge>> g;

const int cInf = 2009000999;
int n;

void Dijkstra(int s) {
  d.assign(n, cInf);
  d[s] = 0;

  std::set<std::pair<int, int>> q;
  q.insert({0, s});

  while (!q.empty()) {
    int v = q.begin()->second;
    q.erase(q.begin());

    if (d[v] == cInf) {
      break;
    }

    for (auto e : g[v]) {
      if (d[v] + e.len < d[e.to]) {
        q.erase({d[e.to], e.to});
        d[e.to] = d[v] + e.len;
        q.insert({d[e.to], e.to});
      }
    }
  }
}

void ProcessGen() {
  int m;
  std::cin >> n >> m;

  g.assign(n, {});
  used.assign(n, false);

  for (int i = 0; i < m; i++) {
    int v;
    int u;
    int w;
    std::cin >> u >> v >> w;
    g[u].push_back({v, w});
    g[v].push_back({u, w});
  }

  int s;
  std::cin >> s;
  Dijkstra(s);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;
  for (int i = 0; i < t; i++) {
    ProcessGen();
    for (auto x : d) {
      std::cout << x << " ";
    }
    std::cout << "\n";
  }
}