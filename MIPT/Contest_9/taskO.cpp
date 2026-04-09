#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

struct Edge {
  int v;
  int u;
  int len;

  bool operator<(const Edge& other) const { return len < other.len; }
};

struct Node {
  Node* parent;
  int s;
};

Node* Get(Node* x) {
  if (x->parent == x) {
    return x;
  }
  return x->parent = Get(x->parent);
}

bool Same(Node* x, Node* y) { return Get(x) == Get(y); }

void Unite(Node* x, Node* y) {
  Node* u = Get(x);
  Node* v = Get(y);

  if (u == v) {
    return;
  }

  if (u->s < v->s) {
    std::swap(u, v);
  }

  v->parent = u;
  u->s += v->s;
}

std::vector<Edge> mst;
int n;

void FindMst(std::vector<Edge>& g) {
  std::sort(g.begin(), g.end());

  std::vector<Node> nodes(n + 1);
  for (int i = 0; i <= n; i++) {
    nodes[i].parent = &nodes[i];
    nodes[i].s = 1;
  }

  for (auto edge : g) {
    Node* u = &nodes[edge.u];
    Node* v = &nodes[edge.v];
    if (!Same(u, v)) {
      mst.push_back(edge);
      Unite(u, v);
    }
  }
}

int main() {
  std::cin >> n;

  std::vector<Edge> g;
  g.reserve(n * (n - 1) / 2 + n);

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int c;
      std::cin >> c;
      if (j > i) {
        g.push_back({i, j, c});
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    int s;
    std::cin >> s;
    g.push_back({0, i, s});
  }

  FindMst(g);

  long long sum = 0;
  for (auto edge : mst) {
    sum += edge.len;
  }

  std::cout << sum << "\n";
}