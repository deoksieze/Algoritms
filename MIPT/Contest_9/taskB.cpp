
#include <iostream>
#include <set>
#include <utility>
#include <vector>

struct Edge {
  int to;
  long long time;
};

std::vector<long> d;
std::vector<long> virus;
std::vector<std::vector<Edge>> g;

const long cInf = 4e18;
int n;

void DijkstraVirus(std::vector<int>& virus_start) {
  virus.assign(n + 1, cInf);
  std::set<std::pair<int, int>> q;

  for (auto i : virus_start) {
    virus[i] = 0;
    q.insert({0, i});
  }

  while (!q.empty()) {
    int v = q.begin()->second;
    q.erase(q.begin());

    if (virus[v] == cInf) {
      break;
    }

    for (auto e : g[v]) {
      if (virus[v] + e.time < virus[e.to]) {
        q.erase({virus[e.to], e.to});
        virus[e.to] = virus[v] + e.time;
        q.insert({virus[e.to], e.to});
      }
    }
  }
}

void DijkstraSurvivor(int s) {
  d.assign(n + 1, cInf);
  std::set<std::pair<int, int>> q;

  d[s] = 0;
  q.insert({0, s});

  while (!q.empty()) {
    int v = q.begin()->second;
    q.erase(q.begin());

    if (d[v] == cInf) {
      break;
    }

    for (auto e : g[v]) {
      if (d[v] + e.time < virus[e.to] && d[v] + e.time < d[e.to]) {
        q.erase({d[e.to], e.to});
        d[e.to] = d[v] + e.time;
        q.insert({d[e.to], e.to});
      }
    }
  }
}

int main() {
  int m;
  int k;
  std::cin >> n >> m >> k;

  std::vector<int> virus_start(k);
  for (int i{}; i < k; i++) {
    std::cin >> virus_start[i];
  }

  g.assign(n + 1, {});

  for (int i = 0; i < m; i++) {
    int v;
    int u;
    int w;
    std::cin >> u >> v >> w;
    g[u].push_back({v, w});
    g[v].push_back({u, w});
  }

  int s;
  int t;
  std::cin >> s >> t;

  DijkstraVirus(virus_start);

  if (virus[s] == 0) {
    std::cout << -1 << "\n";
    return 0;
  }

  DijkstraSurvivor(s);

  if (d[t] == cInf) {
    std::cout << -1;
  } else {
    std::cout << d[t];
  }
  std::cout << "\n";
}