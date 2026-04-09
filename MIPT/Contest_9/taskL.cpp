#include <ios>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

struct Edge {
  int to;
  int len;
  int beauty;
};

struct Vertex {
  int num;
  int len;
  int beauty;

  bool operator<(const Vertex& other) const {
    if (len != other.len) {
      return len < other.len;
    }
    if (beauty != other.beauty) {
      return beauty < other.beauty;
    }
    return num < other.num;
  }
};

std::vector<int> d;
std::vector<std::vector<Edge>> g;

const int cInf = 2009000999;
int n;
int m;

void Dijkstra(int s) {
  d.assign(n + 1, cInf);
  d[s] = 0;

  std::set<Vertex> q;
  q.insert({s, 0, 0});

  while (!q.empty()) {
    Vertex ver = *q.begin();
    int v = ver.num;
    q.erase(q.begin());

    if (d[v] == cInf) {
      break;
    }

    for (auto e : g[v]) {
      if (d[v] + e.len < d[e.to] && e.beauty >= ver.beauty) {
        d[e.to] = d[v] + e.len;
        q.insert({e.to, d[e.to], e.beauty});
      }
    }
  }
}

int main() {
  std::cin >> n >> m;

  g.assign(n + 1, {});

  for (int i = 0; i < m; i++) {
    int v;
    int u;
    int w;
    int b;
    std::cin >> u >> v >> w >> b;
    g[u].push_back({v, w, b});
  }

  Dijkstra(1);

  if (d[n] == cInf) {
    std::cout << -1 << "\n";
  } else {
    std::cout << d[n] << "\n";
  }
}
